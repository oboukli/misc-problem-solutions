// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/two_sum.hpp"

TEST_CASE("Two-Sum problem", "[two_sum]")
{
    using forfun::two_sum::two_sum;

    SECTION("Empty input")
    {
        constexpr std::array<int, 0> const nums{};
        constexpr int const target{0};
        constexpr std::array const expected{-1, -1};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input length is one")
    {
        constexpr std::array const nums{3};
        constexpr int const target{3};
        constexpr std::array const expected{-1, -1};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Input length is two")
    {
        constexpr std::array const nums{3, 3};
        constexpr int const target{6};
        constexpr std::array const expected{0, 1};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Input has negative integers")
    {
        constexpr std::array const nums{0, -1, 2, -3, 1};
        constexpr int const target{-2};
        constexpr std::array const expected{3, 4};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Sorted input 1")
    {
        constexpr std::array const nums{2, 7, 11, 15};
        constexpr int const target{9};
        constexpr std::array const expected{0, 1};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Sorted input 2")
    {
        constexpr std::array const nums{2, 7, 11, 15};
        constexpr int const target{22};
        constexpr std::array const expected{1, 3};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Unsorted input with repeated elements")
    {
        constexpr std::array const nums{19, 19, 19, 19};
        constexpr int const target{38};
        constexpr std::array const expected{0, 1};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Unsorted input 1")
    {
        constexpr std::array const nums{3, 2, 4};
        constexpr int const target{6};
        constexpr std::array const expected{1, 2};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Unsorted input 2")
    {
        constexpr std::array const nums{3, 2, 4};
        constexpr int const target{7};
        constexpr std::array const expected{0, 2};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Unsorted input 3")
    {
        constexpr std::array const nums{1, 4, 10, -3};
        constexpr int const target{14};
        constexpr std::array const expected{1, 2};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }

    SECTION("Unsorted input 4")
    {
        constexpr std::array const nums{9, 5, 1, 23};
        constexpr int const target{10};
        constexpr std::array const expected{0, 2};

        CAPTURE(nums);
        CAPTURE(target);

        constexpr auto const actual{
            two_sum(nums.cbegin(), nums.cend(), target)};

        REQUIRE_THAT(actual, Catch::Matchers::UnorderedRangeEquals(expected));
    }
}
