// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/daily_temperatures.hpp"

TEST_CASE("Daily temperatures", "[daily_temperatures]")
{
    using forfun::daily_temperatures::daily_temperatures;

    SECTION("One day")
    {
        std::array const temperatures{76};
        std::array<int, 1> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 1>
            scratch /*[[indeterminate]]*/;
        std::array const expected{0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Two days (case 1)")
    {
        std::array const temperatures{16, 14};
        std::array<int, 2> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 2>
            scratch /*[[indeterminate]]*/;
        std::array const expected{0, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Two days (case 2)")
    {
        std::array const temperatures{12, 15};
        std::array<int, 2> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 2>
            scratch /*[[indeterminate]]*/;
        std::array const expected{1, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Three days (case 1)")
    {
        std::array const temperatures{14, 14, 14};
        std::array<int, 3> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 3>
            scratch /*[[indeterminate]]*/;
        std::array const expected{0, 0, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Three days (case 2)")
    {
        std::array const temperatures{15, 13, 16};
        std::array<int, 3> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 3>
            scratch /*[[indeterminate]]*/;
        std::array const expected{2, 1, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Four days (case 1)")
    {
        std::array const temperatures{14, 14, 14, 14};
        std::array<int, 4> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 4>
            scratch /*[[indeterminate]]*/;
        std::array const expected{0, 0, 0, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Four days (case 2)")
    {
        std::array const temperatures{14, 13, 12, 15};
        std::array<int, 4> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 4>
            scratch /*[[indeterminate]]*/;
        std::array const expected{3, 2, 1, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Five days")
    {
        std::array const temperatures{17, 13, 15, 16, 20};
        std::array<int, 5> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 5>
            scratch /*[[indeterminate]]*/;
        std::array const expected{4, 1, 1, 1, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("Thirty-two days (benchmark case)")
    {
        std::array const temperatures{
            36, 22, 15, 33, 2,  3,  26, 14, 42, 31, 12, 30, 34, 11, 19, 29,
            7,  41, 8,  21, 23, 32, 6,  13, 24, 20, 39, 27, 35, 37, 43, 25,
        };
        static_assert(temperatures.size() == 32);
        std::array<int, 32> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 32>
            scratch /*[[indeterminate]]*/;
        std::array const expected{
            8, 2,  1, 5, 1, 1, 2, 1, 22, 3, 1, 1, 5, 1, 1, 2,
            1, 13, 1, 1, 1, 5, 1, 1, 2,  1, 4, 1, 1, 1, 0, 0,
        };
        static_assert(expected.size() == 32);

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("LeetCode case 1")
    {
        std::array const temperatures{73, 74, 75, 71, 69, 72, 76, 73};
        std::array<int, 8> day_counts{};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 8>
            scratch /*[[indeterminate]]*/;
        std::array const expected{1, 1, 4, 2, 1, 1, 0, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("LeetCode case 2")
    {
        std::array const temperatures{30, 40, 50, 60};
        std::array<int, 4> day_counts{0};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 4>
            scratch /*[[indeterminate]]*/;
        std::array const expected{1, 1, 1, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("LeetCode case 3")
    {
        std::array const temperatures{30, 60, 90};
        std::array<int, 3> day_counts{0};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 3>
            scratch /*[[indeterminate]]*/;
        std::array const expected{1, 1, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("NeetCode case 1")
    {
        std::array const temperatures{30, 38, 30, 36, 35, 40, 28};
        std::array<int, 7> day_counts{0};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 7>
            scratch /*[[indeterminate]]*/;
        std::array const expected{1, 4, 1, 2, 1, 0, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }

    SECTION("NeetCode case 2")
    {
        std::array const temperatures{22, 21, 20};
        std::array<int, 3> day_counts{0};
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
        std::array<decltype(temperatures)::difference_type, 3>
            scratch /*[[indeterminate]]*/;
        std::array const expected{0, 0, 0};

        CAPTURE(temperatures);

        daily_temperatures(
            std::cbegin(temperatures),
            std::cend(temperatures),
            std::begin(day_counts),
            std::begin(scratch)
        );

        REQUIRE(day_counts == expected);
    }
}

// References:
// https://leetcode.com/problems/daily-temperatures/
// https://neetcode.io/problems/daily-temperatures/
