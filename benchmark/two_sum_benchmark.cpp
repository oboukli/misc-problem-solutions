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
        2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,
        43,  47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101,
        103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
        173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
        241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
    };

    using ConstIter = decltype(nums)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Two sum")
        .relative(true)

        .run(
            NAMEOF_RAW(brute_force::two_sum<ConstIter, ConstIter>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    brute_force::two_sum(nums.cbegin(), nums.cend(), 681)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(map_based::two_sum<ConstIter, ConstIter>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    map_based::two_sum(nums.cbegin(), nums.cend(), 681)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(presorted::two_sum<ConstIter, ConstIter>).c_str(),
            [&nums]() noexcept {
                auto const volatile r{
                    presorted::two_sum(nums.cbegin(), nums.cend(), 681)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
