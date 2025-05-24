// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <cstddef>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/meeting_rooms.hpp"

TEST_CASE("Meeting rooms", "[meeting_rooms]")
{
    using forfun::meeting_rooms::can_attend;
    using forfun::meeting_rooms::interval;

    SECTION("Empty container")
    {
        std::array<interval, 0> const intervals{};

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("One interval")
    {
        std::array const intervals{interval{.start = 9, .end = 17}};

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Two conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 14, .end = 17},
            interval{.start = 14, .end = 15},
        };

        CAPTURE(intervals);

        REQUIRE_FALSE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Two non-conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 10, .end = 11},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Three, all conflicting, intervals")
    {
        std::array const intervals{
            interval{.start = 13, .end = 18},
            interval{.start = 14, .end = 15},
            interval{.start = 14, .end = 19},
        };

        CAPTURE(intervals);

        REQUIRE_FALSE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Three intervals, two of which are conflicting")
    {
        std::array const intervals{
            interval{.start = 9, .end = 14},
            interval{.start = 14, .end = 15},
            interval{.start = 14, .end = 15},
        };

        CAPTURE(intervals);

        REQUIRE_FALSE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Three non-conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 11, .end = 12},
            interval{.start = 13, .end = 14},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Three successive intervals")
    {
        std::array const intervals{
            interval{.start = 11, .end = 12},
            interval{.start = 12, .end = 13},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Four intervals, two of which are conflicting")
    {
        std::array const intervals{
            interval{.start = 9, .end = 11},
            interval{.start = 11, .end = 15},
            interval{.start = 15, .end = 19},
            interval{.start = 18, .end = 20},
        };

        CAPTURE(intervals);

        REQUIRE_FALSE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Four non-conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 9, .end = 11},
            interval{.start = 11, .end = 15},
            interval{.start = 15, .end = 19},
            interval{.start = 19, .end = 20},
        };

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("Sixteen non-conflicting sorted intervals (benchmark case)")
    {
        std::array const intervals{
            interval{.start = 0, .end = 1},
            interval{.start = 1, .end = 2},
            interval{.start = 2, .end = 3},
            interval{.start = 3, .end = 4},
            interval{.start = 4, .end = 5},
            interval{.start = 5, .end = 6},
            interval{.start = 6, .end = 7},
            interval{.start = 7, .end = 8},
            interval{.start = 8, .end = 9},
            interval{.start = 9, .end = 10},
            interval{.start = 10, .end = 11},
            interval{.start = 11, .end = 12},
            interval{.start = 12, .end = 13},
            interval{.start = 13, .end = 14},
            interval{.start = 14, .end = 15},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("NeetCode test case 1")
    {
        std::array const intervals{
            interval{.start = 0, .end = 30},
            interval{.start = 5, .end = 10},
            interval{.start = 15, .end = 20},
        };

        CAPTURE(intervals);

        REQUIRE_FALSE(can_attend(intervals.cbegin(), intervals.cend()));
    }

    SECTION("NeetCode test case 2")
    {
        std::array const intervals{
            interval{.start = 5, .end = 8}, interval{.start = 9, .end = 15}
        };

        CAPTURE(intervals);

        REQUIRE(can_attend(intervals.cbegin(), intervals.cend()));
    }
}

TEST_CASE("Meeting rooms 2", "[meeting_rooms_2]")
{
    using forfun::meeting_rooms::interval;
    using forfun::meeting_rooms::min_chronotopes;

    SECTION("One interval")
    {
        std::array const intervals{interval{.start = 9, .end = 17}};

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 1UZ);
    }

    SECTION("Two conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 14, .end = 17},
            interval{.start = 14, .end = 15},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 2UZ);
    }

    SECTION("Two non-conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 10, .end = 11},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 1UZ);
    }

    SECTION("Three, all conflicting, intervals")
    {
        std::array const intervals{
            interval{.start = 13, .end = 18},
            interval{.start = 14, .end = 15},
            interval{.start = 14, .end = 19},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 3UZ);
    }

    SECTION("Three intervals, two of which are conflicting")
    {
        std::array const intervals{
            interval{.start = 9, .end = 14},
            interval{.start = 14, .end = 15},
            interval{.start = 14, .end = 15},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 2UZ);
    }

    SECTION("Three non-conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 11, .end = 12},
            interval{.start = 13, .end = 14},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 1UZ);
    }

    SECTION("Three successive intervals")
    {
        std::array const intervals{
            interval{.start = 11, .end = 12},
            interval{.start = 12, .end = 13},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 1UZ);
    }

    SECTION("Four intervals, two of which are conflicting")
    {
        std::array const intervals{
            interval{.start = 9, .end = 11},
            interval{.start = 11, .end = 15},
            interval{.start = 15, .end = 19},
            interval{.start = 18, .end = 20},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 2UZ);
    }

    SECTION("Four non-conflicting intervals")
    {
        std::array const intervals{
            interval{.start = 9, .end = 11},
            interval{.start = 11, .end = 15},
            interval{.start = 15, .end = 19},
            interval{.start = 19, .end = 20},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 1UZ);
    }

    SECTION("Sixteen non-conflicting sorted intervals (benchmark case)")
    {
        std::array const intervals{
            interval{.start = 0, .end = 1},
            interval{.start = 1, .end = 2},
            interval{.start = 2, .end = 3},
            interval{.start = 3, .end = 4},
            interval{.start = 4, .end = 5},
            interval{.start = 5, .end = 6},
            interval{.start = 6, .end = 7},
            interval{.start = 7, .end = 8},
            interval{.start = 8, .end = 9},
            interval{.start = 9, .end = 10},
            interval{.start = 10, .end = 11},
            interval{.start = 11, .end = 12},
            interval{.start = 12, .end = 13},
            interval{.start = 13, .end = 14},
            interval{.start = 14, .end = 15},
            interval{.start = 15, .end = 16},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 1UZ);
    }

    SECTION("NeetCode test case 1")
    {
        std::array const intervals{
            interval{.start = 0, .end = 40},
            interval{.start = 5, .end = 10},
            interval{.start = 15, .end = 20},
        };

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 2UZ);
    }

    SECTION("NeetCode test case 2")
    {
        std::array const intervals{interval{.start = 4, .end = 9}};

        CAPTURE(intervals);

        REQUIRE(min_chronotopes(intervals.cbegin(), intervals.cend()) == 1UZ);
    }
}
