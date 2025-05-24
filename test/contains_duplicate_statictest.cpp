// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/contains_duplicate.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Contains duplicate",
    "[contains_duplicate]",
    (auto contains_duplicate, contains_duplicate),
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::array<int, 0>::iterator,
        std::array<int, 0>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::array<int, 0>::iterator,
        std::array<int, 0>::iterator>),
    (forfun::contains_duplicate::stl::contains_duplicate<
        std::array<int, 0>::iterator,
        std::array<int, 0>::iterator>)
)
{
    SECTION("Empty input")
    {
        std::array<int, 0> nums{};
        static constexpr bool const expected{false};

        static constexpr auto const actual{
            contains_duplicate(nums.begin(), nums.end())
        };

        STATIC_REQUIRE(actual == expected);
    }
}

TEST_CASE("Contains duplicate", "[contains_duplicate]")
{
    using forfun::contains_duplicate::quadratic::contains_duplicate;

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
