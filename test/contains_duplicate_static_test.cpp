// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/contains_duplicate.hpp"

TEST_CASE("Contains duplicate", "[contains_duplicate]")
{
    using forfun::contains_duplicate::contains_duplicate;

    SECTION("Empty input")
    {
        static constexpr std::array<int, 0U> const nums{};
        static constexpr bool const expected{false};

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())
        };

        STATIC_REQUIRE(actual == expected);
    }

    SECTION("One integer")
    {
        static constexpr std::array const nums{3};
        static constexpr bool const expected{false};

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())
        };

        STATIC_REQUIRE(actual == expected);
    }

    SECTION("Three integers, one of which is unique")
    {
        static constexpr std::array const nums{19, 7, 19};
        static constexpr bool const expected{true};

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())
        };

        STATIC_REQUIRE(actual == expected);
    }

    SECTION("Three unique integers")
    {
        static constexpr std::array const nums{3, 2, 1};
        static constexpr bool const expected{false};

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())
        };

        STATIC_REQUIRE(actual == expected);
    }
}
