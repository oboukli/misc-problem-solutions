// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/longest_consecutive_sequence.hpp"

using Iter = std::vector<int>::iterator;

TEMPLATE_TEST_CASE_SIG(
    "Longest consecutive sequence",
    "[longest_consecutive_sequence]",
    (auto longest_consecutive, longest_consecutive),
    // clang-format off
    (forfun::longest_consecutive_sequence::counted::
        longest_consecutive<Iter, Iter>),
    (forfun::longest_consecutive_sequence::measured::
        longest_consecutive<Iter, Iter>),
    (forfun::longest_consecutive_sequence::set_scanning::
        longest_consecutive<Iter, Iter>),
    (forfun::longest_consecutive_sequence::set_sliding::
        longest_consecutive<Iter, Iter>)
    // clang-format on
)
{
    SECTION("Empty container")
    {
        std::vector<int> nums{};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 0UZ);
    }

    SECTION("Single element")
    {
        std::vector nums{7};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 1UZ);
    }

    SECTION("Two consecutive elements")
    {
        std::vector nums{7, 8};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 2UZ);
    }

    SECTION("Three consecutive elements")
    {
        std::vector nums{7, 8, 9};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 3UZ);
    }

    SECTION("Four consecutive elements")
    {
        std::vector nums{7, 8, 9, 10};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 4UZ);
    }

    SECTION("Two non-consecutive elements")
    {
        std::vector nums{7, 100};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 1UZ);
    }

    SECTION("Three non-consecutive elements")
    {
        std::vector nums{7, 11, 301};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 1UZ);
    }

    SECTION("Four non-consecutive elements")
    {
        std::vector nums{17, 2, 90, 0};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 1UZ);
    }

    SECTION("Container of consecutive and repeated elements (case 1)")
    {
        std::vector nums{17, 1, 1, 2, 4, 2, 3, 2, 3};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 4UZ);
    }

    SECTION("Container of consecutive and repeated elements (benchmark case)")
    {
        std::vector nums{
            // clang-format off
            1,  1,   2,   3,   44,  45,  46,  47,
            47, 47,  47,  48,  7,   8,   9,   10,
            11, 173, 179, 181, 191, 193, 197, 199,
            22, 23,  24,  211, 283, 293, 307, 311,
            // clang-format on
        };

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 5UZ);
    }

    SECTION("LeetCode case 1")
    {
        std::vector nums{100, 4, 200, 1, 3, 2};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 4UZ);
    }

    SECTION("LeetCode case 2")
    {
        std::vector nums{0, 3, 7, 2, 5, 8, 4, 6, 0, 1};

        CAPTURE(nums);

        REQUIRE(longest_consecutive(nums.begin(), nums.end()) == 9UZ);
    }
}
