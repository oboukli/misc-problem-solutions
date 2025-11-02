// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/forward_list.hpp"

TEST_CASE("Forward list", "[container][forward_list]")
{
    SECTION("Forward list is initially empty")
    {
        static constexpr forfun::experimental::container::forward_list<
            int> const forward_list{};

        STATIC_REQUIRE(forward_list.empty());
    }

    SECTION("Validate reference type")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::experimental::container::forward_list<char>::reference,
                char&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::experimental::container::forward_list<int>::reference,
                int&>
        );
    }

    SECTION("Validate const_reference type")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::experimental::container::forward_list<
                    char>::const_reference,
                char const&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::experimental::container::forward_list<
                    int>::const_reference,
                int const&>
        );
    }

    SECTION("Non-const method front() returns a non-const reference")
    {
        using forward_list = forfun::experimental::container::forward_list<int>;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<forward_list&>().front()),
                forfun::experimental::container::forward_list<int>::reference>
        );
    }

    SECTION("Method `front() const` returns a reference to const (case 1)")
    {
        using forward_list = forfun::experimental::container::forward_list<int>;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<forward_list const&>().front()),
                forfun::experimental::container::forward_list<
                    int>::const_reference>
        );
    }

    SECTION("Method `front()` on an rvalue returns an rvalue reference")
    {
        using forward_list = forfun::experimental::container::forward_list<int>;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<forward_list&&>().front()),
                forfun::experimental::container::forward_list<
                    int>::value_type&&>
        );
    }
}
