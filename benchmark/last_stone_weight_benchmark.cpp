// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/last_stone_weight.hpp"

TEST_CASE("Last stone weight benchmarking", "[benchmark][last_stone_weight]")
{
    using namespace forfun::last_stone_weight;

    using Iter = std::vector<int>::iterator;

    ankerl::nanobench::Bench()

        .title("Last stone weight")
        .relative(true)

        .run(
            NAMEOF_RAW(naive::last_stone_weight<Iter, Iter>).c_str(),
            [] -> void {
                std::vector stones{
                    2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,
                    37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                    83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137,
                    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                    197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                    263, 269, 271, 277, 281, 283, 293, 307, 311,
                };
                auto const volatile r{
                    naive::last_stone_weight(stones.begin(), stones.end())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(priority_queue_based::last_stone_weight).c_str(),
            [] -> void {
                std::vector stones{
                    2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,
                    37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                    83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137,
                    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                    197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                    263, 269, 271, 277, 281, 283, 293, 307, 311,
                };
                auto const volatile r{
                    priority_queue_based::last_stone_weight(std::move(stones))
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(heapified::last_stone_weight<Iter, Iter>).c_str(),
            [] -> void {
                std::vector stones{
                    2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,
                    37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                    83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137,
                    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                    197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                    263, 269, 271, 277, 281, 283, 293, 307, 311,
                };
                auto const volatile r{
                    heapified::last_stone_weight(stones.begin(), stones.end())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(sort_based::last_stone_weight<Iter, Iter>).c_str(),
            [] -> void {
                std::vector stones{
                    2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,
                    37,  41,  43,  47,  53,  59,  61,  67,  71,  73,  79,
                    83,  89,  97,  101, 103, 107, 109, 113, 127, 131, 137,
                    139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193,
                    197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257,
                    263, 269, 271, 277, 281, 283, 293, 307, 311,
                };
                auto const volatile r{
                    sort_based::last_stone_weight(stones.begin(), stones.end())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
