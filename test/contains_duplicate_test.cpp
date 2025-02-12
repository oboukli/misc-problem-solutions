// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/contains_duplicate.hpp"

TEST_CASE("Contains duplicate", "[contains_duplicate]")
{
    using forfun::contains_duplicate::contains_duplicate;

    SECTION("Empty input")
    {
        std::vector<int> const nums{};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("One integer")
    {
        std::vector const nums{3};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Two identical integers")
    {
        std::vector const nums{3, 3};
        bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Two unique items #1")
    {
        std::vector const nums{2, 3};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Two unique items #2")
    {
        std::vector const nums{3, 2};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Three identical integers")
    {
        std::vector const nums{19, 19, 19};
        bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Three integers, one of which is unique")
    {
        std::vector const nums{19, 7, 19};
        bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Three unique integers #1")
    {
        std::vector const nums{2, -5, 3};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Three unique integers #2")
    {
        std::vector const nums{3, 2, 1};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four sorted unique floats")
    {
        std::vector const nums{0.0F, 0.00000001F, 2.0F, 2.001F};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four unsorted unique floats")
    {
        std::vector const nums{2.0F, 2.001F, 0.0F, 0.00000001F};
        bool const expected{false};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Five unsorted floats, two of which are identical")
    {
        std::vector const nums{2.0F, 2.001F, 0.0F, 0.00000001F, 2.001F};
        bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }

    SECTION("Four identical integers")
    {
        std::vector const nums{11, 11, 11, 11};
        bool const expected{true};

        CAPTURE(nums);

        auto const actual{contains_duplicate(nums.cbegin(), nums.cend())};

        REQUIRE(actual == expected);
    }
}
