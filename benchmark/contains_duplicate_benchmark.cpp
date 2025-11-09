// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/contains_duplicate.hpp"

TEST_CASE("Contains duplicate benchmarking", "[benchmark][contains_duplicate]")
{
    using namespace forfun::contains_duplicate;

    using Iter = std::array<int, 32>::iterator;

    ankerl::nanobench::Bench()

        .title("Contains duplicate")
        .relative(true)

        .run(
            NAMEOF_RAW(adjacent_find_based::contains_duplicate<Iter, Iter>)
                .c_str(),
            [] noexcept -> void {
                std::array superprimes{
                    // clang-format off
                    3,   5,   11,  17,  31,  41,  59,  67,
                    83,  109, 127, 157, 179, 191, 211, 241,
                    277, 283, 331, 353, 367, 401, 431, 461,
                    509, 547, 563, 587, 599, 617, 709, 739,
                    // clang-format on
                };

                ankerl::nanobench::doNotOptimizeAway(
                    adjacent_find_based::contains_duplicate(
                        superprimes.begin(), superprimes.end()
                    )
                );
            }
        )

        .run(
            NAMEOF_RAW(quadratic::contains_duplicate<Iter, Iter>).c_str(),
            [] noexcept -> void {
                std::array const superprimes{
                    // clang-format off
                    3,   5,   11,  17,  31,  41,  59,  67,
                    83,  109, 127, 157, 179, 191, 211, 241,
                    277, 283, 331, 353, 367, 401, 431, 461,
                    509, 547, 563, 587, 599, 617, 709, 739,
                    // clang-format on
                };

                ankerl::nanobench::doNotOptimizeAway(
                    quadratic::contains_duplicate(
                        superprimes.cbegin(), superprimes.cend()
                    )
                );
            }
        )

        .run(
            NAMEOF_RAW(sorted::contains_duplicate<Iter, Iter>).c_str(),
            [] noexcept -> void {
                std::array superprimes{
                    // clang-format off
                    3,   5,   11,  17,  31,  41,  59,  67,
                    83,  109, 127, 157, 179, 191, 211, 241,
                    277, 283, 331, 353, 367, 401, 431, 461,
                    509, 547, 563, 587, 599, 617, 709, 739,
                    // clang-format on
                };

                ankerl::nanobench::doNotOptimizeAway(
                    sorted::contains_duplicate(
                        superprimes.begin(), superprimes.end()
                    )
                );
            }
        )

        ;
}
