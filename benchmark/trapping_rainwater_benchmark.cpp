// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/trapping_rainwater.hpp"

TEST_CASE("Trapping rainwater benchmarking", "[benchmark][trapping_rainwater]")
{
    using namespace forfun::trapping_rainwater;

    std::array const elevations{
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

    using ConstIter = decltype(elevations)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Trapping rain water")
        .relative(true)

        .run(
            NAMEOF_RAW(forfun::trapping_rainwater::trap<ConstIter>).c_str(),
            [&elevations] noexcept -> void {
                auto const volatile r{forfun::trapping_rainwater::trap(
                    elevations.cbegin(), elevations.cend()
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
