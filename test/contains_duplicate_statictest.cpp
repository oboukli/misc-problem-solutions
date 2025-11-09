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
    (forfun::contains_duplicate::adjacent_find_based::contains_duplicate<
        std::array<int, 1>::iterator,
        std::array<int, 1>::iterator>),
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::array<int, 1>::iterator,
        std::array<int, 1>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::array<int, 1>::iterator,
        std::array<int, 1>::iterator>),
    (forfun::contains_duplicate::unordered_set_based::contains_duplicate<
        std::array<int, 1>::iterator,
        std::array<int, 1>::iterator>)
)
{
    SECTION("One integer")
    {
        std::array nums{3};

        REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }
}

TEST_CASE("Contains duplicate", "[contains_duplicate]")
{
    using forfun::contains_duplicate::quadratic::contains_duplicate;

    SECTION("Three integers, one of which is unique")
    {
        static constexpr std::array const nums{19, 7, 19};

        STATIC_REQUIRE(contains_duplicate(nums.begin(), nums.end()));
    }

    SECTION("Three unique integers")
    {
        static constexpr std::array const nums{3, 2, 1};

        STATIC_REQUIRE_FALSE(contains_duplicate(nums.begin(), nums.end()));
    }
}
