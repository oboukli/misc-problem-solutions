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

#include <forfun/concurrency/spsc_bound_queue.hpp>

TEST_CASE("Wait-free SPSC append-only bounded queue", "[spsc_bound_queue]")
{
    SECTION("Object representations is not unique")
    {
        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::spsc_bound_queue<
                    char,
                    8,
                    std::hardware_destructive_interference_size>>
        );

        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::spsc_bound_queue<
                    int,
                    8,
                    std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Construction and initialization")
    {
        STATIC_REQUIRE_FALSE(
            std::copyable<forfun::concurrency::wait_free::spsc_bound_queue<
                int,
                8,
                std::hardware_destructive_interference_size>>
        );

        STATIC_REQUIRE_FALSE(
            std::movable<forfun::concurrency::wait_free::spsc_bound_queue<
                int,
                8,
                std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Comparision")
    {
        STATIC_REQUIRE_FALSE(
            std::equality_comparable<
                forfun::concurrency::wait_free::spsc_bound_queue<
                    int,
                    8,
                    std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Capacity is as requested")
    {
        using queue_type = forfun::concurrency::wait_free::spsc_bound_queue<
            int,
            8,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(queue_type::capacity() == 8UZ);
    }

    SECTION("Type aliases")
    {
        using queue_type = forfun::concurrency::wait_free::spsc_bound_queue<
            int,
            8,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(std::same_as<queue_type::size_type, std::size_t>);

        STATIC_REQUIRE(std::same_as<queue_type::value_type, int>);

        STATIC_REQUIRE(std::same_as<queue_type::reference, int&>);
    }

    SECTION("To span")
    {
        using queue_type = forfun::concurrency::wait_free::spsc_bound_queue<
            int,
            8,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(std::same_as<queue_type::span_type, std::span<int>>);

        STATIC_REQUIRE(
            std::same_as<
                queue_type::span_type,
                decltype(std::declval<queue_type>().to_span())>
        );
    }
}
