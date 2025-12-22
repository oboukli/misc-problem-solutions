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

    using Iter = std::array<int, 64>::const_iterator;

    static constexpr int const target{52};

    std::array const records{
        101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
        167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233,
        239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311,
        313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389,
        397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461,
    };
    static_assert(records.size() == 64UZ);

    ankerl::nanobench::Bench()

        .title("Binary search")
        .relative(true)

        .run(
            NAMEOF_RAW(std::find<Iter, int>).c_str(),
            [&records] noexcept -> void {
                // clang-format off
                Iter const r{
                    // NOLINTNEXTLINE(modernize-use-ranges)
                    std::find(records.cbegin(), records.cend(), target)
                };
                // clang-format on
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(std::ranges::find).c_str(),
            [&records] noexcept -> void {
                Iter const r{std::ranges::find(records, target)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(iterative::find<Iter, Iter, int>).c_str(),
            [&records] noexcept -> void {
                Iter const r{
                    iterative::find(records.cbegin(), records.cend(), target)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(recursive::find<Iter, Iter, int>).c_str(),
            [&records] noexcept -> void {
                Iter const r{
                    recursive::find(records.cbegin(), records.cend(), target)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
