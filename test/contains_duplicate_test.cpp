// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/contains_duplicate.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Contains duplicate",
    "[contains_duplicate]",
    (auto contains_duplicate, contains_duplicate),
    (forfun::contains_duplicate::adjacent_find_based::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>),
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>)
)
{
    SECTION("One integer")
    {
        std::vector nums{3};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Two identical integers")
    {
        std::vector nums{3, 3};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Two unique items #1")
    {
        std::vector nums{2, 3};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Two unique items #2")
    {
        std::vector nums{3, 2};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three identical integers")
    {
        std::vector nums{19, 19, 19};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three integers, one of which is unique")
    {
        std::vector nums{19, 7, 19};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three unique integers #1")
    {
        std::vector nums{2, -5, 3};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three unique integers #2")
    {
        std::vector nums{3, 2, 1};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Four identical integers")
    {
        std::vector nums{11, 11, 11, 11};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Contains duplicate",
    "[contains_duplicate]",
    (auto contains_duplicate, contains_duplicate),
    (forfun::contains_duplicate::adjacent_find_based::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>),
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>)
)
{
    SECTION("Four sorted unique floats")
    {
        std::vector nums{0.0F, 0.00000001F, 2.0F, 2.001F};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Four unsorted unique floats")
    {
        std::vector nums{2.0F, 2.001F, 0.0F, 0.00000001F};

        CAPTURE(nums);

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Five unsorted floats, two of which are identical")
    {
        std::vector nums{2.0F, 2.001F, 0.0F, 0.00000001F, 2.001F};

        CAPTURE(nums);

        REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }
}

TEST_CASE(
    "Contains duplicate (empty input degenerate case)", "[contains_duplicate]"
)
{
    using forfun::contains_duplicate::adjacent_find_based::contains_duplicate;

    std::vector<int> nums{};

    CAPTURE(nums);

    REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
}
