// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>

#include <catch2/catch_test_macros.hpp>

#include "forfun_c/mem/mem.h"

namespace {

extern "C" {

[[nodiscard]] auto dummy_malloc(std::size_t /*unused*/) noexcept -> void*;

auto dummy_free(void* /*unused*/) noexcept -> void;

[[nodiscard]] auto dummy_malloc(std::size_t /*unused*/) noexcept -> void*
{
    return nullptr;
}

auto dummy_free(void* /*unused*/) noexcept -> void
{
}

} // extern "C"

} // namespace

TEST_CASE("Memory allocator manager", "[mem]")
{
    SECTION("Confirm default global state")
    {
        ::forfun_mem_reset_to_default();
        ::forfun_mem const mem_current_state{::forfun_mem_get()};

        REQUIRE(mem_current_state.ff_malloc == &std::malloc);
        REQUIRE(mem_current_state.ff_free == &std::free);
    }

    SECTION("Set to dummy allocator then reset to default configuration")
    {
        ::forfun_mem_reset_to_default();
        ::forfun_mem const mem_current_state{::forfun_mem_get()};

        ::forfun_mem const mem{
            .ff_malloc = &dummy_malloc,
            .ff_free = &dummy_free,
        };

        REQUIRE_FALSE(mem.ff_malloc == mem_current_state.ff_malloc);
        REQUIRE_FALSE(mem.ff_free == mem_current_state.ff_free);

        ::forfun_mem_set(mem);
        ::forfun_mem const mem_state_after_set{::forfun_mem_get()};

        REQUIRE(mem_state_after_set.ff_malloc == &dummy_malloc);
        REQUIRE(mem_state_after_set.ff_free == &dummy_free);

        ::forfun_mem_reset_to_default();
        ::forfun_mem const mem_reset_state{::forfun_mem_get()};

        REQUIRE(mem_reset_state.ff_malloc == &std::malloc);
        REQUIRE(mem_reset_state.ff_free == &std::free);
    }
}
