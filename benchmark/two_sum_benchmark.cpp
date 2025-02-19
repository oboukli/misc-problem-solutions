// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/two_sum.hpp"

TEST_CASE("Two sum benchmarking", "[benchmark][two_sum]")
{
    using namespace forfun::two_sum;

    std::array const nums{
        // clang-format off
        131, 89,  61,  37,  103,  5,    41,  73,
        233, 127, 101, 163, 283,  109,  257, 263,
        191, 79,  11,  97,  1601, 7,    211, 43,
        281, 179, 2,   271, 223,  181,  13,  137,
        3,   53,  157, 277, 193,  1607, 71,  269,
        139, 151, 167, 83,  47,   199,  59,  239,
        229, 293, 173, 241, 251,  19,   227, 67,
        17,  197, 29,  113, 149,  31,   107, 23,
        // clang-format on
    };

    using ConstIter = decltype(nums)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Two sum")
        .relative(true)

        .run(
            NAMEOF_RAW(quadratic::two_sum<ConstIter, ConstIter>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    quadratic::two_sum(nums.cbegin(), nums.cend(), 3208)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(map_based::two_sum<ConstIter, ConstIter>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    map_based::two_sum(nums.cbegin(), nums.cend(), 3208)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}

TEST_CASE("Two sum II benchmarking", "[benchmark][two_sum]")
{
    using namespace forfun::two_sum;

    std::array const nums{
        // clang-format off
        2,   3,   5,   7,   11,  13,  17,   19,
        23,  29,  31,  37,  41,  43,  47,   53,
        59,  61,  67,  71,  73,  79,  83,   89,
        97,  101, 103, 107, 109, 113, 127,  131,
        137, 139, 149, 151, 157, 163, 167,  173,
        179, 181, 191, 193, 197, 199, 211,  223,
        227, 229, 233, 239, 241, 251, 257,  263,
        269, 271, 277, 281, 283, 293, 1601, 1607,
        // clang format on
    };

    using ConstIter = decltype(nums)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Two sum II")
        .relative(true)

        .run(
            NAMEOF_RAW(quadratic::two_sum<ConstIter, ConstIter>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    quadratic::two_sum(nums.cbegin(), nums.cend(), 3208)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(map_based::two_sum<ConstIter, ConstIter>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    map_based::two_sum(nums.cbegin(), nums.cend(), 3208)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

    .run(
        NAMEOF_RAW(presorted::two_sum<ConstIter, ConstIter>).c_str(),
        [&nums]() noexcept {
            auto const volatile r{
                presorted::two_sum(nums.cbegin(), nums.cend(), 3208)
            };
            ankerl::nanobench::doNotOptimizeAway(&r);
        }
    )

    ;
}
