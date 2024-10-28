// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/search/binary_search.hpp"

TEST_CASE("Binary search benchmarking", "[benchmark][search][binary_search]")
{
    using namespace forfun::search::binary_search;
    using Itr = std::array<int, 12U>::const_iterator;

    std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    static_assert(records.size() == 12U);

    ankerl::nanobench::Bench()

        .title("Binary search")
        .relative(true)

        .run(
            NAMEOF_RAW(std::find<Itr, int>).c_str(),
            [&records]() noexcept {
                // NOLINTNEXTLINE(modernize-use-ranges)
                Itr const r{std::find(records.cbegin(), records.cend(), 41)};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(std::ranges::find).c_str(),
            [&records]() noexcept {
                Itr const r{std::ranges::find(records, 41)};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(iterative::find<Itr, int>).c_str(),
            [&records]() noexcept {
                Itr const r{
                    iterative::find(records.cbegin(), records.cend(), 41)
                };
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(recursive::find<Itr, int>).c_str(),
            [&records]() noexcept {
                Itr const r{
                    recursive::find(records.cbegin(), records.cend(), 41)
                };
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
