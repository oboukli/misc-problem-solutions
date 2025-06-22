// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_container_properties.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/graph/subsets.hpp"

TEST_CASE("Subsets", "[subsets]")
{
    using forfun::subsets::explode_subsets;

    SECTION("Empty container")
    {
        std::vector<int> const elements{};

        std::vector<std::vector<int>> const expected{{}};

        CAPTURE(elements);

        auto const actual{explode_subsets(elements)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(1U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("One element container")
    {
        std::vector const elements{17};

        std::vector<std::vector<int>> const expected{{}, {17}};

        CAPTURE(elements);

        auto const actual{explode_subsets(elements)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(2U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Two element container")
    {
        std::vector const elements{5, 7};

        std::vector<std::vector<int>> const expected{{{}, {5}, {7}, {5, 7}}};

        CAPTURE(elements);

        auto const actual{explode_subsets(elements)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(4U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Three element container")
    {
        std::vector const elements{1, 2, 3};

        std::vector<std::vector<int>> const expected{
            {{}, {1}, {2}, {1, 2}, {3}, {1, 3}, {2, 3}, {1, 2, 3}}
        };

        CAPTURE(elements);

        auto const actual{explode_subsets(elements)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(8U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }

    SECTION("Four element container")
    {
        std::vector const elements{23, 29, 31, 37};

        std::vector<std::vector<int>> const expected{
            {},
            {23},
            {29},
            {31},
            {37},
            {23, 29},
            {23, 31},
            {23, 37},
            {29, 31},
            {29, 37},
            {31, 37},
            {23, 29, 31},
            {23, 31, 37},
            {23, 29, 37},
            {29, 31, 37},
            {23, 29, 31, 37}
        };

        CAPTURE(elements);

        auto const actual{explode_subsets(elements)};

        REQUIRE_THAT(
            actual,
            Catch::Matchers::SizeIs(16U)
                and Catch::Matchers::UnorderedRangeEquals(expected)
        );
    }
}
