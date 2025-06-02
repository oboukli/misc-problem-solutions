// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <limits>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/single_number.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Single number",
    "[single_number]",
    (auto get_single, get_single),
    forfun::single_number::functional::get_single<std::vector<int> const&>,
    forfun::single_number::imperative::get_single<std::vector<int> const&>
)
{
    SECTION("Zero")
    {
        std::vector<int> const nums{0};

        REQUIRE(get_single(nums) == 0);
    }

    SECTION("One")
    {
        std::vector const nums{1};

        REQUIRE(get_single(nums) == 1);
    }

    SECTION("Negative number")
    {
        std::vector const nums{-1};

        REQUIRE(get_single(nums) == -1);
    }

    SECTION("Three numbers")
    {
        std::vector const nums{-2, 19, -2};

        REQUIRE(get_single(nums) == 19);
    }

    SECTION("Positive and negative numbers where the single number is positive")
    {
        std::vector const nums{2, -2, 0, 0, 11, 2, -2};

        REQUIRE(get_single(nums) == 11);
    }

    SECTION("Positive and negative numbers where the single number is negative")
    {
        std::vector const nums{5, 2, -1, -13, 2, -1, 5};

        REQUIRE(get_single(nums) == -13);
    }

    SECTION("Limits of int")
    {
        // https://en.wikipedia.org/wiki/Delicate_prime
        static constexpr int const delicate_prime{4393139};

        std::vector const nums{
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min(),
            delicate_prime,
            std::numeric_limits<int>::max(),
            std::numeric_limits<int>::min(),
        };

        REQUIRE(get_single(nums) == delicate_prime);
    }

    SECTION("Thirty-one numbers (benchmark case)")
    {
        std::vector const nums{
            // clang-format off
            1,  1,  2,  2,  3,  3,  4,   4,
            5,  5,  6,  6,  7,  7,  8,   8,
            9,  9,  10, 10, 11, 11, 12,  12,
            13, 13, 14, 14, 15, 15, 101,
            // clang-format off
        };

        REQUIRE(get_single(nums) == 101);
    }

    SECTION("LeetCode case 1")
    {
        std::vector const nums{2, 2, 1};

        REQUIRE(get_single(nums) == 1);
    }

    SECTION("LeetCode case 2")
    {
        std::vector const nums{4, 1, 2, 1, 2};

        REQUIRE(get_single(nums) == 4);
    }

    SECTION("NeetCode case 1")
    {
        std::vector const nums{3, 2, 3};

        REQUIRE(get_single(nums) == 2);
    }

    SECTION("NeetCode case 2")
    {
        std::vector const nums{7, 6, 6, 7, 8};

        REQUIRE(get_single(nums) == 8);
    }
}

// References:
// - https://leetcode.com/problems/single-number/
// - https://neetcode.io/problems/single-number
