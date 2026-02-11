// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/valid_sudoku.hpp"

TEST_CASE("Valid Sudoku benchmarking", "[benchmark][valid_sudoku]")
{
    using namespace forfun::valid_sudoku;

    SudokuBoard<std::uint8_t> board{{
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},
    }};

    ankerl::nanobench::Bench()

        .title("Valid Sudoku")
        .relative(true)

        .run(
            NAMEOF_RAW(bitwise::is_valid_sudoku<std::uint8_t>).c_str(),
            [&board] noexcept -> void {
                auto const volatile r{bitwise::is_valid_sudoku(board)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(stl_bitset::is_valid_sudoku<std::uint8_t>).c_str(),
            [&board] noexcept -> void {
                auto const volatile r{stl_bitset::is_valid_sudoku(board)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
