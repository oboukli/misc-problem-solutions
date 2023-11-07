// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include "forfun/contains_duplicate.hpp"

TEST_CASE("Contains Duplicate", "[contains_duplicate]")
{
    using forfun::contains_duplicate::contains_duplicate;

    SECTION("Empty input")
    {
        constexpr std::array<int, 0> const nums{};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is one")
    {
        constexpr std::array const nums{3};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is two and contains duplicates")
    {
        constexpr std::array const nums{3, 3};
        constexpr bool const expected{true};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is two and contains unique items #1")
    {
        constexpr std::array const nums{2, 3};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is two and contains unique items #2")
    {
        constexpr std::array const nums{3, 2};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains only duplicates")
    {
        constexpr std::array const nums{19, 19, 19};
        constexpr bool const expected{true};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains two duplicates")
    {
        constexpr std::array const nums{19, 7, 19};
        constexpr bool const expected{true};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains only unique items #1")
    {
        constexpr std::array const nums{2, -5, 3};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains only unique items #2")
    {
        constexpr std::array const nums{3, 2, 1};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input is of four sorted unique elements")
    {
        constexpr std::array const nums{0.0f, 0.00000001f, 2.0f, 2.001f};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input is of four unsorted unique elements")
    {
        constexpr std::array const nums{2.0f, 2.001f, 0.0f, 0.00000001f};
        constexpr bool const expected{false};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input is of four repeated elements")
    {
        constexpr std::array const nums{11, 11, 11, 11};
        constexpr bool const expected{true};

        CAPTURE(nums);

        constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }
}
