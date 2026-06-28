// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/daily_temperatures.hpp"

TEST_CASE("Daily temperatures benchmarking", "[benchmark][daily_temperatures]")
{
    using namespace forfun::daily_temperatures;

    std::array const temperatures{
        36, 22, 15, 33, 2,  3,  26, 14, 42, 31, 12, 30, 34, 11, 19, 29,
        7,  41, 8,  21, 23, 32, 6,  13, 24, 20, 39, 27, 35, 37, 43, 25,
    };

    std::array<int, 32> day_counts{};
    std::array<decltype(temperatures)::difference_type, 32> scratch{};

    using ConstIter = decltype(temperatures)::const_iterator;
    using OutIter = decltype(day_counts)::iterator;
    using ScratchIter = decltype(scratch)::iterator;

    ankerl::nanobench::Bench()

        .title("Daily temperatures")
        .relative(true)

        .run(
            // clang-format off
            NAMEOF_RAW(
                daily_temperatures<ConstIter, ConstIter, OutIter, ScratchIter>
            ).c_str(),
            // clang-format on
            [&temperatures, &day_counts, &scratch] noexcept -> void {
                daily_temperatures(
                    std::cbegin(temperatures),
                    std::cend(temperatures),
                    std::begin(day_counts),
                    std::begin(scratch)
                );

                ankerl::nanobench::doNotOptimizeAway(&day_counts);
            }
        )

        ;
}
