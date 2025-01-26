// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/house_robber.hpp"

TEST_CASE("House robber benchmarking", "[benchmark][house_robber]")
{
    using namespace forfun::house_robber;

    std::vector const stashes{
        2,   5,   11,  17,  23,  29,  41,  47,  53,  59,  71,
        83,  89,  101, 107, 113, 131, 137, 149, 167, 173, 179,
        191, 197, 227, 233, 239, 251, 257, 263, 269, 271,
    };

    using ConstIter = decltype(stashes)::const_iterator;

    ankerl::nanobench::Bench()

        .title("House robber")
        .relative(true)

        .run(
            NAMEOF_RAW(recursive::rob<ConstIter, ConstIter>).c_str(),
            [&stashes]() noexcept {
                auto const volatile r{
                    recursive::rob(stashes.cbegin(), stashes.cend())
                };

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
