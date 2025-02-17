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
using ConstIter3UZ = std::array<int, 3U>::const_iterator;

TEMPLATE_TEST_CASE_SIG(
    "Two sum (I, II) static tests (empty container)",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::presorted::two_sum<ConstIter0UZ, ConstIter0UZ>),
    (forfun::two_sum::quadratic::two_sum<ConstIter0UZ, ConstIter0UZ>)
)
{
    static constexpr std::array<int, 0U> const nums{};
    static constexpr int const target{0};
    static constexpr std::array const expected{nums.cend(), nums.cend()};

    static constexpr auto const actual{
        two_sum(nums.cbegin(), nums.cend(), target)
    };

    STATIC_REQUIRE(actual == expected);
}

TEMPLATE_TEST_CASE_SIG(
    "Two sum static tests (unsorted three-element container)",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::quadratic::two_sum<ConstIter3UZ, ConstIter3UZ>)
)
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

TEMPLATE_TEST_CASE_SIG(
    "Two sum (I, II) static tests (container sorted in non-descending order)",
    "[two_sum]",
    (auto two_sum, two_sum),
    (forfun::two_sum::presorted::two_sum<ConstIter3UZ, ConstIter3UZ>),
    (forfun::two_sum::quadratic::two_sum<ConstIter3UZ, ConstIter3UZ>)
)
{
    static constexpr std::array const nums{2, 3, 4};
    static constexpr int const target{6};
    static constexpr std::array const expected{
        nums.cbegin(), std::next(nums.cbegin(), 2)
    };

    static constexpr auto const actual{
        two_sum(nums.cbegin(), nums.cend(), target)
    };

    STATIC_REQUIRE(actual == expected);
}
