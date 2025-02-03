// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <iterator>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/two_sum.hpp"

using ConstIter0UZ = std::array<int, 0U>::const_iterator;
using ConstIter1UZ = std::array<int, 3U>::const_iterator;

TEMPLATE_TEST_CASE_SIG(
    "Two sum static tests",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::brute_force::two_sum<ConstIter0UZ, ConstIter0UZ>)
)
{
    SECTION("Empty input")
    {
        static constexpr std::array<int, 0U> const nums{};
        static constexpr int const target{0};
        static constexpr std::array const expected{nums.cend(), nums.cend()};

        static constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)
        };

        STATIC_REQUIRE(actual == expected);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Two sum static tests",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::brute_force::two_sum<ConstIter1UZ, ConstIter1UZ>)
)
{
    SECTION("Unsorted input")
    {
        static constexpr std::array const nums{3, 2, 4};
        static constexpr int const target{6};
        static constexpr std::array const expected{
            std::next(nums.cbegin(), 1), std::next(nums.cbegin(), 2)
        };

        static constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)
        };

        STATIC_REQUIRE(actual == expected);
    }
}
