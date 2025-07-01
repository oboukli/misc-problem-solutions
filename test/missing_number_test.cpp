// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/missing_number.hpp"

namespace {

using Range = std::vector<int>;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Missing number",
    "[missing_number]",
    (auto find_missing_number, find_missing_number),
    forfun::missing_number::bitwise::find_missing_number<Range const&>,
    forfun::missing_number::functional::find_missing_number<Range const&>,
    forfun::missing_number::imperative::find_missing_number<Range const&>,
    forfun::missing_number::optimized::find_missing_number<Range const&>
)
{
    SECTION("One number (case 1)")
    {
        std::vector const nums{0};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 1);
    }

    SECTION("One number (case 2)")
    {
        std::vector const nums{1};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 0);
    }

    SECTION("Ten numbers")
    {
        std::vector const nums{4, 3, 9, 10, 1, 2, 7, 5, 6, 0};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 8);
    }

    SECTION("Sixteen numbers (benchmark case)")
    {
        std::vector const nums{
            14, 1, 16, 6, 8, 4, 5, 15, 2, 9, 13, 3, 10, 7, 0, 12
        };

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 11);
    }

    SECTION("LeetCode case 1")
    {
        std::vector const nums{3, 0, 1};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 2);
    }

    SECTION("LeetCode case 2")
    {
        std::vector const nums{0, 1};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 2);
    }

    SECTION("LeetCode case 3")
    {
        std::vector const nums{9, 6, 4, 2, 3, 5, 7, 0, 1};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 8);
    }

    SECTION("NeetCode case 1")
    {
        std::vector const nums{1, 2, 3};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 0);
    }

    SECTION("NeetCode case 2")
    {
        std::vector const nums{0, 2};

        CAPTURE(nums);

        REQUIRE(find_missing_number(nums) == 1);
    }
}

// References:
// https://leetcode.com/problems/missing-number/
// https://neetcode.io/problems/missing-number
