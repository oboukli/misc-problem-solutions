// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/search/koko_eating_bananas.hpp"

TEST_CASE(
    "Koko eating bananas benchmarking", "[benchmark][koko_eating_bananas]"
)
{
    using namespace forfun::search;

    using PileType = std::array<int, 16>;
    using ConstIter = PileType::const_iterator;

    static constexpr int const duration{17};

    PileType piles{
        311,
        383,
        359,
        367,
        313,
        307,
        317,
        337,
        347,
        353,
        331,
        379,
        349,
        283,
        373,
        293,
    };

    ankerl::nanobench::Bench()

        .title("Koko eating bananas")
        .relative(true)

        .run(
            NAMEOF_RAW(
                koko_eating_bananas::min_eating_speed<ConstIter, ConstIter>
            )
                .c_str(),
            [&piles] noexcept -> void {
                auto const volatile r{koko_eating_bananas::min_eating_speed(
                    piles.cbegin(), piles.cend(), duration
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
