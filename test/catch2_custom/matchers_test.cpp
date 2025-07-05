// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>

#include "matchers.hpp"

TEST_CASE("UnorderedNestedRangeEquals", "[matchers]")
{
    using forfun::testing::catch2_custom::matchers::UnorderedNestedRangeEquals;

    SECTION("Empty")
    {
        static constexpr std::array<std::array<int, 0>, 0> const expected{};
        static constexpr std::array<std::array<int, 0>, 0> const actual{};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("One of one")
    {
        std::vector<std::vector<int>> const expected{{1}};
        static constexpr std::array<std::array<int, 1>, 1> const actual{{{1}}};

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Matching number containers")
    {
        std::vector<std::vector<int>> const expected{{1, 2, 3}, {4, 5, 6}};
        static constexpr std::array<std::array<int, 3>, 2> const actual{
            {{1, 2, 3}, {4, 5, 6}}
        };

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Matching unordered containers of numbers")
    {
        std::vector<std::vector<int>> const expected{{}, {4, 5}, {17, 11, 13}};
        std::array<std::vector<int>, 3> const actual{
            {{4, 5}, {}, {13, 17, 11}}
        };

        REQUIRE_THAT(actual, UnorderedNestedRangeEquals(expected));
    }

    SECTION("Unmatching number containers")
    {
        std::vector<std::vector<int>> const expected{{9, 2, 3}, {4, 5, 6}};
        static constexpr std::array<std::array<int, 3>, 2> const actual{
            {{4, 5, 6}, {1, 2, 3}}
        };

        REQUIRE_THAT(actual, not UnorderedNestedRangeEquals(expected));
    }

    SECTION("Unmatching inner container sizes")
    {
        std::vector<std::vector<int>> const expected{{5003, 5009}, {5011}};
        std::vector<std::vector<int>> const actual{
            {5003, 5009, 5011, 5021}, {5003, 5009, 5011, 5021, 5023, 5039}
        };

        REQUIRE_THAT(actual, not UnorderedNestedRangeEquals(expected));
    }

    SECTION("Description")
    {
        std::vector<std::vector<int>> const expected{
            {127, 227, 131}, {109, 239, 113}
        };

        auto const matcher{UnorderedNestedRangeEquals(expected)};

        REQUIRE(
            matcher.describe()
            == "unordered elements are { { 127, 227, 131 }, { 109, 239, 113 } }"
        );

        static constexpr std::array<std::array<int, 3>, 2> const actual{
            {{4, 5, 6}, {1, 2, 3}}
        };
        REQUIRE_FALSE(matcher.match(actual));

        REQUIRE(
            matcher.describe()
            == "unordered elements are { { 127, 227, 131 }, { 109, 239, 113 } }"
        );
    }
}
