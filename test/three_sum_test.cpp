// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "catch2_custom/matchers.hpp"

#include "forfun/three_sum.hpp"

namespace {

using CIter = std::vector<int>::const_iterator;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Three sum",
    "[three_sum]",
    (auto three_sum, three_sum),
    (forfun::three_sum::non_presorted::brute_force::three_sum<CIter, CIter>),
    (forfun::three_sum::non_presorted::set_based::three_sum<CIter, CIter>)
)
{
    using forfun::testing::catch2_custom::matchers::UnorderedNestedRangeEquals;

    SECTION("Three numbers with one three-sum")
    {
        std::vector const nums{3, -5, 2};
        std::vector<std::array<int, 3>> const expected{{-5, 2, 3}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Three numbers without a three-sum (case 1)")
    {
        std::vector const nums{0, 7, -6};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Four numbers with one three-sum")
    {
        std::vector const nums{11, 7, -10, 3};
        std::vector<std::array<int, 3>> const expected{{-10, 3, 7}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Four numbers without a three-sum (case 1)")
    {
        std::vector const nums{11, 7, -10, 5};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four negative numbers")
    {
        std::vector const nums{-1, -3, -4, -2};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four numbers without a three-sum (case 2)")
    {
        std::vector const nums{2, 4, 3, 1};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Five numbers with one three-sum")
    {
        std::vector const nums{-9, 5, 4, 4, 3};
        std::vector<std::array<int, 3>> const expected{{-9, 4, 5}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Five numbers with two distinct three-sums")
    {
        std::vector const nums{3, -3, 0, 2, -2};
        std::vector<std::array<int, 3>> const expected{{-3, 0, 3}, {-2, 0, 2}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Five numbers with duplicate three-sums")
    {
        std::vector const nums{3, -3, 0, -3, -3};
        std::vector<std::array<int, 3>> const expected{{-3, 0, 3}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Five positive numbers")
    {
        std::vector const nums{2, 11, 3, 7, 15};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Eight numbers")
    {
        std::vector const nums{-1, 1, -1, 1, -1, 1, 2, 0};
        std::vector<std::array<int, 3>> const expected{{-1, -1, 2}, {-1, 0, 1}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Twelve numbers")
    {
        std::vector const nums{10, -5, -5, -1, -1, 10, 0, 1, 1, 1, 0, -5};
        std::vector<std::array<int, 3>> const expected{
            {-5, -5, 10}, {-1, 0, 1}
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Sixteen numbers (case 1)")
    {
        std::vector const nums{
            -1, 1, -1, 1, -1, 1, 2, 0, -1, -1, 2, -4, -4, -4, 3, -3
        };
        std::vector<std::array<int, 3>> const expected{
            {-4, 1, 3},
            {-4, 2, 2},
            {-3, 0, 3},
            {-3, 1, 2},
            {-1, -1, 2},
            {-1, 0, 1},
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Sixteen numbers (case 2)")
    {
        std::vector const nums{
            -10, -10, -10, 6, -2, 0, 3, 4, 4, 5, 5, 5, -10, 6, 6, 7
        };
        std::vector<std::array<int, 3>> const expected{
            {-10, 3, 7},
            {-10, 4, 6},
            {-10, 5, 5},
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Thirty-two numbers (benchmark unsorted case)")
    {
        std::vector const nums{
            // clang-format off
            0,   15,  21, 5,   3, 7,  -7,  6,
            -10, -5,  4,  30,  2, 11, 3,   20,
            10,  20,  5,  -10, 6, 3,  -10, -2,
            4,   -10, 17, -6,  5, 17, 6,   7,
            // clang-format on
        };
        std::vector<std::array<int, 3>> const expected{
            {-10, -10, 20},
            {-10, -7, 17},
            {-10, -5, 15},
            {-10, 0, 10},
            {-10, 3, 7},
            {-10, 4, 6},
            {-10, 5, 5},
            {-7, 0, 7},
            {-7, 2, 5},
            {-7, 3, 4},
            {-6, -5, 11},
            {-6, 0, 6},
            {-6, 2, 4},
            {-6, 3, 3},
            {-5, -2, 7},
            {-5, 0, 5},
            {-5, 2, 3},
            {-2, 0, 2},
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Wikipedia case")
    {
        std::vector const nums{-25, 2, 10, -10, 8, -7, -3, 4};
        std::vector<std::array<int, 3>> const expected{
            {-10, 2, 8}, {-7, -3, 10}
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("LeetCode case 1")
    {
        std::vector const nums{-1, 0, 1, 2, -1, -4};
        std::vector<std::array<int, 3>> const expected{{-1, -1, 2}, {-1, 0, 1}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("LeetCode case 2")
    {
        std::vector const nums{1, 0, 1};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Three sum (presorted input)",
    "[three_sum]",
    (auto three_sum, three_sum),
    (forfun::three_sum::non_presorted::brute_force::three_sum<CIter, CIter>),
    (forfun::three_sum::non_presorted::set_based::three_sum<CIter, CIter>),
    (forfun::three_sum::presorted::set_map_based::three_sum<CIter, CIter>),
    (forfun::three_sum::presorted::two_pointer::three_sum<CIter, CIter>)
)
{
    using forfun::testing::catch2_custom::matchers::UnorderedNestedRangeEquals;

    SECTION("Three zeros")
    {
        std::vector const nums{0, 0, 0};
        std::vector<std::array<int, 3>> const expected{{0, 0, 0}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Three numbers with one three-sum")
    {
        std::vector const nums{-5, 2, 3};
        std::vector<std::array<int, 3>> const expected{{-5, 2, 3}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Three numbers without a three-sum (case 1)")
    {
        std::vector const nums{-6, 0, 7};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Three numbers without a three-sum (case 2)")
    {
        std::vector const nums{1, 1, 1};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four zeros")
    {
        std::vector const nums{0, 0, 0, 0};
        std::vector<std::array<int, 3>> const expected{{0, 0, 0}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four numbers with one three-sum")
    {
        std::vector const nums{-10, 3, 7, 11};
        std::vector<std::array<int, 3>> const expected{{-10, 3, 7}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Four numbers without a three-sum (case 1)")
    {
        std::vector const nums{-10, 5, 7, 11};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four negative numbers")
    {
        std::vector const nums{-4, -3, -2, -1};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four numbers without a three-sum (case 2)")
    {
        std::vector const nums{1, 2, 3, 4};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Five numbers with one three-sum")
    {
        std::vector const nums{-9, 3, 4, 4, 5};
        std::vector<std::array<int, 3>> const expected{{-9, 4, 5}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Five numbers with two distinct three-sums")
    {
        std::vector const nums{-3, -2, 0, 2, 3};
        std::vector<std::array<int, 3>> const expected{{-3, 0, 3}, {-2, 0, 2}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Five numbers with duplicate three-sums")
    {
        std::vector const nums{-3, -3, -3, 0, 3};
        std::vector<std::array<int, 3>> const expected{{-3, 0, 3}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Five positive numbers")
    {
        std::vector const nums{2, 3, 5, 7, 11};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Eight numbers")
    {
        std::vector const nums{-1, -1, -1, 0, 1, 1, 1, 2};
        std::vector<std::array<int, 3>> const expected{{-1, -1, 2}, {-1, 0, 1}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Twelve numbers")
    {
        std::vector const nums{-5, -5, -5, -1, -1, 0, 0, 1, 1, 1, 10, 10};
        std::vector<std::array<int, 3>> const expected{
            {-5, -5, 10}, {-1, 0, 1}
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Sixteen numbers (case 1)")
    {
        std::vector const nums{
            -4, -4, -4, -3, -1, -1, -1, -1, -1, 0, 1, 1, 1, 2, 2, 3
        };
        std::vector<std::array<int, 3>> const expected{
            {-4, 1, 3},
            {-4, 2, 2},
            {-3, 0, 3},
            {-3, 1, 2},
            {-1, -1, 2},
            {-1, 0, 1},
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Sixteen numbers (case 2)")
    {
        std::vector const nums{
            -10, -10, -10, -10, -2, 0, 3, 4, 4, 5, 5, 5, 6, 6, 6, 7
        };
        std::vector<std::array<int, 3>> const expected{
            {-10, 3, 7},
            {-10, 4, 6},
            {-10, 5, 5},
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Thirty-two numbers (benchmark sorted case)")
    {
        std::vector const nums{
            // clang-format off
            -10, -10, -10, -10, -7, -6, -5, -2,
            0,   2,   3,   3,   3,  4,  4,  5,
            5,   5,   6,   6,   6,  7,  7,  10,
            11,  15,  17,  17,  20, 20, 21, 30,
            // clang-format on
        };
        std::vector<std::array<int, 3>> const expected{
            {-10, -10, 20},
            {-10, -7, 17},
            {-10, -5, 15},
            {-10, 0, 10},
            {-10, 3, 7},
            {-10, 4, 6},
            {-10, 5, 5},
            {-7, 0, 7},
            {-7, 2, 5},
            {-7, 3, 4},
            {-6, -5, 11},
            {-6, 0, 6},
            {-6, 2, 4},
            {-6, 3, 3},
            {-5, -2, 7},
            {-5, 0, 5},
            {-5, 2, 3},
            {-2, 0, 2},
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Wikipedia case")
    {
        std::vector const nums{-25, -10, -7, -3, 2, 4, 8, 10};
        std::vector<std::array<int, 3>> const expected{
            {-10, 2, 8}, {-7, -3, 10}
        };

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("LeetCode case 1")
    {
        std::vector const nums{-4, -1, -1, 0, 1, 2};
        std::vector<std::array<int, 3>> const expected{{-1, -1, 2}, {-1, 0, 1}};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("LeetCode case 2")
    {
        std::vector const nums{0, 1, 1};
        std::vector<std::array<int, 3>> const expected{};

        CAPTURE(nums);

        auto const actual{three_sum(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }
}
