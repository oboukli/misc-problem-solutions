// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <type_traits>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/concurrency/spsc_bound_queue.hpp"

namespace {

[[nodiscard]] consteval auto is_constexpr_destructor() noexcept -> bool
{
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 8> const queue{};
    }

    return true;
}

} // namespace

TEST_CASE("Wait-free SPSC append-only bounded queue", "[spsc_bound_queue]")
{
    SECTION("Object representations is not unique")
    {
        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::spsc_bound_queue<char, 8>>
        );

        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::spsc_bound_queue<int, 8>>
        );
    }

    SECTION("Construction and initialization")
    {
        STATIC_REQUIRE_FALSE(
            std::copyable<
                forfun::concurrency::wait_free::spsc_bound_queue<int, 8>>
        );

        STATIC_REQUIRE_FALSE(
            std::movable<
                forfun::concurrency::wait_free::spsc_bound_queue<int, 8>>
        );
    }

    SECTION("Destructor call on empty queue")
    {
        STATIC_REQUIRE(is_constexpr_destructor());
    }

    SECTION("Comparision")
    {
        STATIC_REQUIRE_FALSE(
            std::equality_comparable<
                forfun::concurrency::wait_free::spsc_bound_queue<int, 8>>
        );
    }

    SECTION("Capacity")
    {
        STATIC_REQUIRE(
            forfun::concurrency::wait_free::spsc_bound_queue<int, 8>::capacity()
            == 8UZ
        );
    }

    SECTION("To span")
    {
        using queue_type
            = forfun::concurrency::wait_free::spsc_bound_queue<int, 8>;

        STATIC_REQUIRE(
            std::same_as<
                queue_type::span_type,
                decltype(std::declval<queue_type>().to_span())>
        );
    }
}
