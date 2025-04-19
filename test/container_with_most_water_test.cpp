// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/container_with_most_water.hpp"

namespace {

using CIter = std::vector<int>::const_iterator;

} // namespace

TEST_CASE(
    "Container with most water (empty container degenerate case)",
    "[container_with_most_water]"
)
{
    using forfun::container_with_most_water::brute::calc_max_area;

    std::vector<int> const input{};

    CAPTURE(input);

    REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 0);
}

TEMPLATE_TEST_CASE_SIG(
    "Container with most water",
    "[container_with_most_water]",
    (auto calc_max_area, calc_max_area),
    (forfun::container_with_most_water::brute::calc_max_area<CIter, CIter>),
    (forfun::container_with_most_water::enhanced::calc_max_area<CIter, CIter>)
)
{
    SECTION("No area possible (one element degenerate case)")
    {
        std::vector const input{7};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 0);
    }

    SECTION("Two heights (case 1)")
    {
        std::vector const input{0, 0};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 0);
    }

    SECTION("Two heights (case 2)")
    {
        std::vector const input{1, 1};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 1);
    }

    SECTION("Two heights (case 3)")
    {
        std::vector const input{2, 3};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == (2 * 1));
    }

    SECTION("Three heights")
    {
        std::vector const input{71, 83, 89};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == (71 * 2));
    }

    SECTION("Four heights")
    {
        std::vector const input{19, 31, 29, 23};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 19 * 3);
    }

    SECTION("Equal heights")
    {
        std::vector const input{1, 1, 1, 1, 1};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 4);
    }

    SECTION("Leftmost case")
    {
        std::vector const input{16, 20, 5, 5, 1};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 16 * 1);
    }

    SECTION("Rightmost case")
    {
        std::vector const input{1, 1, 5, 50, 50};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 50 * 1);
    }

    SECTION("Thirty-two heights (benchmark case)")
    {
        std::vector const input{
            2,   4,  6,  8,  10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 257,
            257, 29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9,  7,  5,  3,  1,
        };

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 257);
    }

    SECTION("LeetCode case")
    {
        std::vector const input{1, 8, 6, 2, 5, 4, 8, 3, 7};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 49);
    }

    SECTION("NeetCode case")
    {
        std::vector const input{2, 2, 2};

        CAPTURE(input);

        REQUIRE(calc_max_area(input.cbegin(), input.cend()) == 4);
    }
}

// References:
// https://leetcode.com/problems/container-with-most-water/
// https://neetcode.io/problems/max-water-container
