// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/meeting_rooms.hpp"

TEST_CASE("Meeting rooms benchmarking", "[benchmark][meeting_rooms]")
{
    using namespace forfun::meeting_rooms;

    std::vector<interval> const intervals{
        {.start = 0, .end = 1},
        {.start = 1, .end = 2},
        {.start = 2, .end = 3},
        {.start = 3, .end = 4},
        {.start = 4, .end = 5},
        {.start = 5, .end = 6},
        {.start = 6, .end = 7},
        {.start = 7, .end = 8},
        {.start = 8, .end = 9},
        {.start = 9, .end = 10},
        {.start = 10, .end = 11},
        {.start = 11, .end = 12},
        {.start = 12, .end = 13},
        {.start = 13, .end = 14},
        {.start = 14, .end = 15},
        {.start = 15, .end = 16},
    };

    using Iter = decltype(intervals)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Meeting rooms")
        .relative(true)

        .run(
            NAMEOF_RAW(can_attend<Iter, Iter>).c_str(),
            [&intervals] noexcept -> void {
                auto const volatile r{
                    can_attend(intervals.cbegin(), intervals.cend())
                };

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}

TEST_CASE("Meeting rooms 2 benchmarking", "[benchmark][meeting_rooms_2]")
{
    using namespace forfun::meeting_rooms;

    std::vector<interval> const intervals{
        {.start = 0, .end = 1},
        {.start = 1, .end = 2},
        {.start = 2, .end = 3},
        {.start = 3, .end = 4},
        {.start = 4, .end = 5},
        {.start = 5, .end = 6},
        {.start = 6, .end = 7},
        {.start = 7, .end = 8},
        {.start = 8, .end = 9},
        {.start = 9, .end = 10},
        {.start = 10, .end = 11},
        {.start = 11, .end = 12},
        {.start = 12, .end = 13},
        {.start = 13, .end = 14},
        {.start = 14, .end = 15},
        {.start = 15, .end = 16},
    };

    using Iter = decltype(intervals)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Meeting rooms 2")
        .relative(true)

        .run(
            NAMEOF_RAW(min_chronotopes<Iter, Iter>).c_str(),
            [&intervals] noexcept -> void {
                auto const volatile r{
                    min_chronotopes(intervals.cbegin(), intervals.cend())
                };

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
