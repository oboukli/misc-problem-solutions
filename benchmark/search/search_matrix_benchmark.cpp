// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/search/search_matrix.hpp"

TEST_CASE("Search matrix benchmarking", "[benchmark][search_matrix]")
{
    using namespace forfun::search::search_matrix;

    static constexpr int const target{397};

    std::vector<std::vector<int>> const matrix{
        {101, 103, 107, 109, 113, 127, 131, 137},
        {139, 149, 151, 157, 163, 167, 173, 179},
        {181, 191, 193, 197, 199, 211, 223, 227},
        {229, 233, 239, 241, 251, 257, 263, 269},
        {271, 277, 281, 283, 293, 307, 311, 313},
        {317, 331, 337, 347, 349, 353, 359, 367},
        {373, 379, 383, 389, 397, 401, 409, 419},
        {421, 431, 433, 439, 443, 449, 457, 461},
    };

    ankerl::nanobench::Bench()

        .title("Search matrix")
        .relative(true)

        .run(
            NAMEOF_RAW(approach_a::find).c_str(),
            [&matrix] noexcept -> void {
                auto const volatile r{approach_a::find(matrix, target)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(approach_b::find).c_str(),
            [&matrix] noexcept -> void {
                auto const volatile r{approach_b::find(matrix, target)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
