// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>
#include <limits>
#include <memory>

#include <catch2/catch_test_macros.hpp>

#include "forfun_c/common.h"
#include "forfun_c/mem/mem.h"
#include "forfun_c/shim/allocator.h"

TEST_CASE("Shim memory allocator", "[shim_allocator]")
{
    SECTION("Confirm assumptions about mem state before enabling shim")
    {
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);

        ::forfun_mem const mem_current_state{::forfun_mem_get()};

        REQUIRE_FALSE(mem_current_state.ff_malloc == &::forfun_shim_malloc);
        REQUIRE_FALSE(mem_current_state.ff_free == &::forfun_shim_free);
    }

    SECTION("Confirm state after enabling shim")
    {
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);

        ::forfun_mem const mem_current_state{::forfun_mem_get()};

        REQUIRE_FALSE(mem_current_state.ff_malloc == &::forfun_shim_malloc);
        REQUIRE_FALSE(mem_current_state.ff_free == &::forfun_shim_free);

        REQUIRE(::forfun_shim_enable() == 0);

        ::forfun_mem const mem_state_after_shim_enable{::forfun_mem_get()};

        REQUIRE(mem_state_after_shim_enable.ff_malloc == &::forfun_shim_malloc);
        REQUIRE(mem_state_after_shim_enable.ff_free == &::forfun_shim_free);

        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_TRUE);

        ::forfun_shim_disable();
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);
    }

    SECTION("Confirm global state after disabling shim")
    {
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);

        REQUIRE(::forfun_shim_enable() == 0);

        ::forfun_mem const mem_current_state{::forfun_mem_get()};

        REQUIRE(mem_current_state.ff_malloc == &::forfun_shim_malloc);
        REQUIRE(mem_current_state.ff_free == &::forfun_shim_free);

        ::forfun_shim_disable();

        ::forfun_mem const mem_state_after_shim_disable{::forfun_mem_get()};

        REQUIRE_FALSE(
            mem_state_after_shim_disable.ff_malloc == &::forfun_shim_malloc
        );
        REQUIRE_FALSE(
            mem_state_after_shim_disable.ff_free == &::forfun_shim_free
        );

        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);
    }

    SECTION("Error on enabling already enabled shim")
    {
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);

        REQUIRE(::forfun_shim_enable() == 0);
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_TRUE);

        REQUIRE(::forfun_shim_enable() == 1);
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_TRUE);

        ::forfun_shim_disable();
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);

        REQUIRE(::forfun_shim_enable() == 0);
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_TRUE);

        ::forfun_shim_disable();
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);
    }

    SECTION("Confirm shim initial state")
    {
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Reset shim state")
    {
        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Mutate then reset shim state")
    {
        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );

        ::forfun_shim_set_malloc_fail_after(7919);
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 7919);

        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Happy journey of shim malloc and shim free invocations")
    {
        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );

        {
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };

            REQUIRE_FALSE(ptr.get() == nullptr);
        }

        REQUIRE(::forfun_shim_get_malloc_call_count() == 1);
        REQUIRE(::forfun_shim_get_free_call_count() == 1);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );

        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Shim simulate error on first invocation")
    {
        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );

        ::forfun_shim_set_malloc_fail_after(0);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 0);

        {
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };

            REQUIRE(ptr.get() == nullptr);
        }

        REQUIRE(::forfun_shim_get_malloc_call_count() == 1);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 0);

        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Shim simulate error on fifth invocation")
    {
        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );

        ::forfun_shim_set_malloc_fail_after(4);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 4);

        {
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr1{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr2{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr3{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr4{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr5{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };

            REQUIRE_FALSE(ptr1.get() == nullptr);
            REQUIRE_FALSE(ptr2.get() == nullptr);
            REQUIRE_FALSE(ptr3.get() == nullptr);
            REQUIRE_FALSE(ptr4.get() == nullptr);
            REQUIRE(ptr5.get() == nullptr);
        }

        REQUIRE(::forfun_shim_get_malloc_call_count() == 5);
        REQUIRE(::forfun_shim_get_free_call_count() == 4);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 4);

        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Shim simulate error on sixth invocation")
    {
        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );

        ::forfun_shim_set_malloc_fail_after(5);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 5);

        {
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr1{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr2{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr3{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr4{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr5{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr6{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };

            REQUIRE_FALSE(ptr1.get() == nullptr);
            REQUIRE_FALSE(ptr2.get() == nullptr);
            REQUIRE_FALSE(ptr3.get() == nullptr);
            REQUIRE_FALSE(ptr4.get() == nullptr);
            REQUIRE_FALSE(ptr5.get() == nullptr);
            REQUIRE(ptr6.get() == nullptr);
        }

        REQUIRE(::forfun_shim_get_malloc_call_count() == 6);
        REQUIRE(::forfun_shim_get_free_call_count() == 5);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 5);

        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Shim simulate errors after seventh invocation")
    {
        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );

        ::forfun_shim_set_malloc_fail_after(7);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 7);

        {
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr1{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr2{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr3{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr4{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr5{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr6{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr7{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr8{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };
            std::unique_ptr<void, decltype(&::forfun_shim_free)> const ptr9{
                ::forfun_shim_malloc(sizeof(int)), &::forfun_shim_free
            };

            REQUIRE_FALSE(ptr1.get() == nullptr);
            REQUIRE_FALSE(ptr2.get() == nullptr);
            REQUIRE_FALSE(ptr3.get() == nullptr);
            REQUIRE_FALSE(ptr4.get() == nullptr);
            REQUIRE_FALSE(ptr5.get() == nullptr);
            REQUIRE_FALSE(ptr6.get() == nullptr);
            REQUIRE_FALSE(ptr7.get() == nullptr);
            REQUIRE(ptr8.get() == nullptr);
            REQUIRE(ptr9.get() == nullptr);
        }

        REQUIRE(::forfun_shim_get_malloc_call_count() == 9);
        REQUIRE(::forfun_shim_get_free_call_count() == 7);
        REQUIRE(::forfun_shim_get_malloc_fail_after() == 7);

        ::forfun_shim_reset();
        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    SECTION("Invoking shim free with nullptr")
    {
        ::forfun_shim_reset();

        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);

        ::forfun_shim_free(nullptr);

        REQUIRE(::forfun_shim_get_free_call_count() == 1);

        ::forfun_shim_reset();
    }

    SECTION("Assert clean state after at test case end")
    {
        REQUIRE(::forfun_shim_is_enabled() == ::FORFUN_FALSE);

        ::forfun_mem const mem_current_state{::forfun_mem_get()};

        REQUIRE_FALSE(mem_current_state.ff_malloc == &::forfun_shim_malloc);
        REQUIRE_FALSE(mem_current_state.ff_free == &::forfun_shim_free);

        REQUIRE(::forfun_shim_get_malloc_call_count() == 0);
        REQUIRE(::forfun_shim_get_free_call_count() == 0);
        REQUIRE(
            ::forfun_shim_get_malloc_fail_after()
            == std::numeric_limits<std::size_t>::max()
        );
    }

    // Do not mutate any (global) state beyond the last section.
}
