// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <cstddef>
#include <new>
#include <span>
#include <type_traits>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include <forfun/concurrency/swmr_append_buffer.hpp>

TEST_CASE("Wait-free SWMR append buffer", "[swmr_append_buffer]")
{
    SECTION("Object representations is not unique")
    {
        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::swmr_append_buffer<
                    char,
                    8,
                    std::hardware_destructive_interference_size>>
        );

        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::swmr_append_buffer<
                    int,
                    8,
                    std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Construction and initialization")
    {
        STATIC_REQUIRE_FALSE(
            std::copyable<forfun::concurrency::wait_free::swmr_append_buffer<
                int,
                8,
                std::hardware_destructive_interference_size>>
        );

        STATIC_REQUIRE_FALSE(
            std::movable<forfun::concurrency::wait_free::swmr_append_buffer<
                int,
                8,
                std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Comparision")
    {
        STATIC_REQUIRE_FALSE(
            std::equality_comparable<
                forfun::concurrency::wait_free::swmr_append_buffer<
                    int,
                    8,
                    std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Capacity is as requested")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(buffer_type::capacity() == 8UZ);
    }

    SECTION("Type aliases")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(std::same_as<buffer_type::size_type, std::size_t>);

        STATIC_REQUIRE(std::same_as<buffer_type::value_type, int>);

        STATIC_REQUIRE(std::same_as<buffer_type::reference, int&>);
    }

    SECTION("To span")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(std::same_as<buffer_type::span_type, std::span<int>>);

        STATIC_REQUIRE(
            std::same_as<
                buffer_type::span_type,
                decltype(std::declval<buffer_type>().to_span())>
        );
    }
}
