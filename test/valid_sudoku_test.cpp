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

    SECTION("Wikipedia example (benchmark case)")
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

    SECTION("Invalid case 1")
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
            {0, 0, 0, 4, 1, 9, 0, 2, 5}, // Repeated 2
            {0, 0, 0, 0, 8, 0, 0, 7, 9},
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("Invalid case 2")
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
            {0, 9, 0, 0, 8, 0, 0, 7, 9}, // Repeated 9
            // clang-format on
        }};

        CAPTURE(board);

        REQUIRE_FALSE(is_valid_sudoku(board));
    }

    SECTION("LeetCode case 1")
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

    SECTION("LeetCode case 2")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {8, 3, 0, 0, 7, 0, 0, 0, 0},
            {6, 0, 0, 1, 9, 5, 0, 0, 0},
            {0, 9, 8, 0, 0, 0, 0, 6, 0}, // Repeated 8
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

    SECTION("NeetCode case 1")
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

    SECTION("NeetCode case 2")
    {
        SudokuBoard<std::uint8_t> const board{{
            // clang-format off
            {1, 2, 0, 0, 3, 0, 0, 0, 0},
            {4, 0, 0, 5, 0, 0, 0, 0, 0},
            {0, 9, 1, 0, 0, 0, 0, 0, 3}, // Repeated 1
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
