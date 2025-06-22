// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/graph/subsets.hpp"

TEST_CASE("Subsets benchmarking", "[benchmark][subsets]")
{
    using namespace forfun;

    std::vector const elements{23, 29, 31, 37};

    ankerl::nanobench::Bench()

        .title("Subsets")
        .relative(true)

        .run(
            NAMEOF_RAW(subsets::explode_subsets).c_str(),
            [&elements]() noexcept {
                auto const volatile r{subsets::explode_subsets(elements)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
