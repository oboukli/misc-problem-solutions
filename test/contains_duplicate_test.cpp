// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/contains_duplicate.hpp"

TEST_CASE("Contains Duplicate", "[contains_duplicate]")
{
    using forfun::contains_duplicate::contains_duplicate;

    SECTION("Empty input")
    {
        static constexpr std::array<int, 0> const nums{};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        STATIC_REQUIRE(actual == expected);
    }

    SECTION("Input length is one")
    {
        static constexpr std::array const nums{3};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is two and contains duplicates")
    {
        static constexpr std::array const nums{3, 3};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is two and contains unique items #1")
    {
        static constexpr std::array const nums{2, 3};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is two and contains unique items #2")
    {
        static constexpr std::array const nums{3, 2};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains only duplicates")
    {
        static constexpr std::array const nums{19, 19, 19};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains two duplicates")
    {
        static constexpr std::array const nums{19, 7, 19};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains only unique items #1")
    {
        static constexpr std::array const nums{2, -5, 3};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input length is three and contains only unique items #2")
    {
        static constexpr std::array const nums{3, 2, 1};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input is of four sorted unique elements")
    {
        static constexpr std::array const nums{0.0F, 0.00000001F, 2.0F, 2.001F};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input is of four unsorted unique elements")
    {
        static constexpr std::array const nums{2.0F, 2.001F, 0.0F, 0.00000001F};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Input is of four repeated elements")
    {
        static constexpr std::array const nums{11, 11, 11, 11};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        static constexpr auto const actual{
            contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }
}
