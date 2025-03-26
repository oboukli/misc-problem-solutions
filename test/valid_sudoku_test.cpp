// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/valid_sudoku.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Valid Sudoku",
    "[valid_sudoku]",
    (auto is_valid_sudoku, is_valid_sudoku),
    forfun::valid_sudoku::bitwise::is_valid_sudoku<std::uint8_t>,
    forfun::valid_sudoku::stl_bitset::is_valid_sudoku<std::uint8_t>
)
{
    using forfun::valid_sudoku::SudokuBoard;

    SECTION("Wikipedia example (valid benchmark case)")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE(is_valid_sudoku(board));
    }

    SECTION("Invalid block")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 2, 5}, // Repeated 2 in block.
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid column and row")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 9, 0, 0, 8, 0, 0, 7, 9}, // Repeated 9 in column and row.
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("LeetCode valid case")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE(is_valid_sudoku(board));
    }

    SECTION("LeetCode invalid case")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {8, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0}, // Repeated 8 in block.
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("NeetCode valid case")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {1, 2, 0, 0, 3, 0, 0, 0, 0},
            {4, 0, 0, 5, 0, 0, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 0, 3},
            {5, 0, 0, 0, 6, 0, 0, 0, 4},
            {0, 0, 0, 8, 0, 3, 0, 0, 5},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 0, 0, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 8},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE(is_valid_sudoku(board));
    }

    SECTION("NeetCode invalid case")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {1, 2, 0, 0, 3, 0, 0, 0, 0},
            {4, 0, 0, 5, 0, 0, 0, 0, 0},
            {0, 9, 1, 0, 0, 0, 0, 0, 3}, // Repeated 1 in block.
            {5, 0, 0, 0, 6, 0, 0, 0, 4},
            {0, 0, 0, 8, 0, 3, 0, 0, 5},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 0, 0, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 8},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE_FALSE(is_valid_sudoku(board));
    }
}
