// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/valid_sudoku.hpp"

namespace {

using CellType = std::uint8_t;

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Valid Sudoku",
    "[valid_sudoku]",
    (auto is_valid_sudoku, is_valid_sudoku),
    forfun::valid_sudoku::bitwise::is_valid_sudoku<CellType>,
    forfun::valid_sudoku::stl_bitset::is_valid_sudoku<CellType>
)
{
    using forfun::valid_sudoku::SudokuBoard;

    SECTION("Wikipedia example (valid benchmark case)")
    {
        static constexpr SudokuBoard<CellType> const board{{
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

        REQUIRE(is_valid_sudoku(board));
    }

    SECTION("Empty Sudoku")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
        }};

        REQUIRE(is_valid_sudoku(board));
    }

    SECTION("All invalid Sudoku board")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
            {3, 3, 3, 3, 3, 3, 3, 3, 3},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid row")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 4, 3, 0, 0, 1}, // Repeated 4 in row.
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid column")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {5, 3, 0, 0, 0, 0, 0, 7, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 7, 5}, // Repeated 7 in column.
            {0, 0, 0, 0, 8, 0, 0, 0, 0},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid block")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 2, 5}, // Repeated 2 in block.
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid column and row")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {5, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0},
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 9, 0, 0, 8, 0, 0, 7, 9}, // Repeated 9 in column and row.
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid column and block")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 5, 0, 0, 0},
            {0, 0, 0, 0, 5, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 5, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid row and block")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 6, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {6, 0, 0, 0, 6, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid column, row, and block")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {0, 0, 0, 0, 0, 0, 0, 0, 9},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 9, 0},
            {9, 0, 0, 0, 0, 0, 0, 0, 9},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("LeetCode valid case")
    {
        static constexpr SudokuBoard<CellType> const board{{
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

        REQUIRE(is_valid_sudoku(board));
    }

    SECTION("LeetCode invalid case")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {8, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0}, // Repeated 8 in block.
            {8, 0, 0, 0, 6, 0, 0, 0, 3},
            {4, 0, 0, 8, 0, 3, 0, 0, 1},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 6, 0, 0, 0, 0, 2, 8, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 5},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("NeetCode valid case")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {1, 2, 0, 0, 3, 0, 0, 0, 0},
            {4, 0, 0, 5, 0, 0, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 0, 3},
            {5, 0, 0, 0, 6, 0, 0, 0, 4},
            {0, 0, 0, 8, 0, 3, 0, 0, 5},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 0, 0, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 8},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        }};

        REQUIRE(is_valid_sudoku(board));
    }

    SECTION("NeetCode invalid case")
    {
        static constexpr SudokuBoard<CellType> const board{{
            {1, 2, 0, 0, 3, 0, 0, 0, 0},
            {4, 0, 0, 5, 0, 0, 0, 0, 0},
            {0, 9, 1, 0, 0, 0, 0, 0, 3}, // Repeated 1 in block.
            {5, 0, 0, 0, 6, 0, 0, 0, 4},
            {0, 0, 0, 8, 0, 3, 0, 0, 5},
            {7, 0, 0, 0, 2, 0, 0, 0, 6},
            {0, 0, 0, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 4, 1, 9, 0, 0, 8},
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
        }};

        REQUIRE_FALSE(is_valid_sudoku(board));
    }
}
