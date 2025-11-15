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
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>),
    (forfun::contains_duplicate::stl::contains_duplicate<
        std::vector<int>::iterator,
        std::vector<int>::iterator>)
)
{
    SECTION("One integer")
    {
        std::vector nums{3};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Two identical integers")
    {
        std::vector nums{3, 3};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Two unique items #1")
    {
        std::vector nums{2, 3};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Two unique items #2")
    {
        std::vector nums{3, 2};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Three identical integers")
    {
        std::vector nums{19, 19, 19};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Three integers, one of which is unique")
    {
        std::vector nums{19, 7, 19};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Three unique integers #1")
    {
        std::vector nums{2, -5, 3};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Three unique integers #2")
    {
        std::vector nums{3, 2, 1};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Four identical integers")
    {
        std::vector nums{11, 11, 11, 11};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Contains duplicate",
    "[contains_duplicate]",
    (auto contains_duplicate, contains_duplicate),
    (forfun::contains_duplicate::quadratic::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>),
    (forfun::contains_duplicate::sorted::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>),
    (forfun::contains_duplicate::stl::contains_duplicate<
        std::vector<float>::iterator,
        std::vector<float>::iterator>)
)
{
    SECTION("Four sorted unique floats")
    {
        std::vector nums{0.0F, 0.00000001F, 2.0F, 2.001F};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Four unsorted unique floats")
    {
        std::vector nums{2.0F, 2.001F, 0.0F, 0.00000001F};
        static constexpr bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }

    SECTION("Five unsorted floats, two of which are identical")
    {
        std::vector nums{2.0F, 2.001F, 0.0F, 0.00000001F, 2.001F};
        static constexpr bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.begin(), nums.end())};

        REQUIRE(actual == expected);
    }
}

TEST_CASE(
    "Contains duplicate (empty input degenerate case)", "[contains_duplicate]"
)
{
    using forfun::contains_duplicate::stl::contains_duplicate;

    std::vector<int> nums{};
    static constexpr bool const expected{false};

    CAPTURE(nums);

    auto const actual{contains_duplicate(nums.begin(), nums.end())};

    REQUIRE(actual == expected);
}
