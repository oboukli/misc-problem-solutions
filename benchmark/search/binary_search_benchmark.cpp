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
    using Iter = std::array<int, 12>::const_iterator;

    std::array const records{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    static_assert(records.size() == 12UZ);

    ankerl::nanobench::Bench()

        .title("Binary search")
        .relative(true)

        .run(
            NAMEOF_RAW(std::find<Iter, int>).c_str(),
            [&records] noexcept -> void {
                // NOLINTNEXTLINE(modernize-use-ranges)
                Iter const r{std::find(records.cbegin(), records.cend(), 41)};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(std::ranges::find).c_str(),
            [&records] noexcept -> void {
                Iter const r{std::ranges::find(records, 41)};
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(iterative::find<Iter, Iter, int>).c_str(),
            [&records] noexcept -> void {
                Iter const r{
                    iterative::find(records.cbegin(), records.cend(), 41)
                };
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(recursive::find<Iter, Iter, int>).c_str(),
            [&records] noexcept -> void {
                Iter const r{
                    recursive::find(records.cbegin(), records.cend(), 41)
                };
                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
