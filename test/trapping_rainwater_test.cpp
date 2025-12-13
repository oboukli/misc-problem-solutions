// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "forfun/trapping_rainwater.hpp"

TEST_CASE("Trapping Rainwater", "[trapping_rainwater]")
{
    using forfun::trapping_rainwater::trap;

    SECTION("Sea level")
    {
        std::array<int, 1> const elevations{0};

        CHECK(elevations.size() == 1UZ);

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("One elevation")
    {
        std::array<int, 1> const elevations{11};

        CHECK(elevations.size() == 1UZ);

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("Two elevations, both are zero")
    {
        std::array const elevations{0, 0};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("Two elevations, left is zero")
    {
        std::array const elevations{0, 2};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("Two elevations, right is zero")
    {
        std::array const elevations{5, 0};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("two elevations, capacity is 0")
    {
        std::array const elevations{3, 5};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("Three elevations, capacity is zero (case 1)")
    {
        std::array const elevations{0, 0, 0};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("Three elevations, capacity is zero (case 2)")
    {
        std::array const elevations{0, 3, 4};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 0);
    }

    SECTION("Three elevations, capacity is 4 (case 1)")
    {
        std::array const elevations{5, 0, 4};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 4);
    }

    SECTION("Three elevations, capacity is 4 (case 2)")
    {
        std::array const elevations{4, 0, 5};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 4);
    }

    SECTION("Three elevations, capacity is 3")
    {
        std::array const elevations{4, 1, 5};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 3);
    }

    SECTION("Six elevations, capacity is 5")
    {
        std::array const elevations{4, 7, 0, 5, 4, 2};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 5);
    }

    SECTION("Sixty-four elevations, capacity is 27,583 (benchmark case)")
    {
        // clang-format off
        std::array const elevations{
            131, 89,  61,  37,  103,  5,    41,  73,
            233, 127, 101, 163, 283,  109,  257, 263,
            191, 79,  11,  97,  1601, 7,    211, 43,
            281, 179, 2,   271, 223,  181,  13,  137,
            3,   53,  157, 277, 193,  1607, 71,  269,
            139, 151, 167, 83,  47,   199,  59,  239,
            229, 293, 173, 241, 251,  19,   227, 67,
            17,  197, 29,  113, 149,  31,   107, 23,
        };
        // clang-format on

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 27'583);
    }

    SECTION("LeetCode (case 1)")
    {
        std::array const elevations{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 6);
    }

    SECTION("LeetCode (case 2)")
    {
        std::array const elevations{4, 2, 0, 3, 2, 5};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 9);
    }

    SECTION("NeetCode (case 1)")
    {
        std::array const elevations{0, 2, 0, 3, 1, 0, 1, 3, 2, 1};

        CAPTURE(elevations);

        REQUIRE(trap(elevations.cbegin(), elevations.cend()) == 9);
    }

    SECTION("Three floating point elevations (case 1)")
    {
        std::array const elevations{4.3F, 1.1F, 5.6F};

        CAPTURE(elevations);

        REQUIRE_THAT(
            trap(elevations.cbegin(), elevations.cend()),
            Catch::Matchers::WithinRel(3.2F)
        );
    }

    SECTION("Three floating point elevations (case 2)")
    {
        std::array const elevations{5.6F, 1.1F, 4.3F};

        CAPTURE(elevations);

        REQUIRE_THAT(
            trap(elevations.cbegin(), elevations.cend()),
            Catch::Matchers::WithinRel(3.2F)
        );
    }
}

// References:
/// https://leetcode.com/problems/trapping-rain-water/
/// https://neetcode.io/problems/trapping-rain-water/
