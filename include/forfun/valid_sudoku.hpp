// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Sudoku

#ifndef FORFUN_VALID_SUDOKU_HPP_
#define FORFUN_VALID_SUDOKU_HPP_

#include <array>
#include <bitset>
#include <concepts>
#include <cstddef>

namespace forfun::valid_sudoku {

template <std::integral CellType>
using SudokuBoard = std::array<std::array<CellType, 9U>, 9U>;

namespace bitwise {

namespace detail {

[[nodiscard]] constexpr auto tick_out(auto const cell, auto& set) noexcept
    -> bool
{
    if (cell != decltype(cell){0})
    {
        if (((1U << (cell - 1U)) & set) == 0U)
        {
            return false;
        }

        set ^= (1U << (cell - 1U));
    }

    return true;
}

} // namespace detail

template <typename CellType>
[[nodiscard]] constexpr auto
is_valid_sudoku(SudokuBoard<CellType> const& board) noexcept -> bool
{
    using SetType = unsigned int;

    static constexpr unsigned initval{0x1FF};

    // clang-format off
        std::array<SetType, 9U> rows{
            initval, initval, initval, initval, initval,
            initval, initval, initval, initval,
        };
        std::array<SetType, 9U> boxes{
            initval, initval, initval, initval, initval,
            initval, initval, initval, initval,
        };
    // clang-format on

    for (std::size_t i{}; i < board.size(); ++i)
    {
        SetType col{initval};

        for (std::size_t j{}; j < board.size(); ++j)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
            if (not detail::tick_out(board[i][j], col))
            {
                return false;
            }

            if (not detail::tick_out(board[j][i], rows[i]))
            {
                return false;
            }

            if (not detail::tick_out(
                    board[(3 * (i / 3)) + (j / 3)][(3 * (i % 3)) + (j % 3)],
                    boxes[i]
                ))
            {
                return false;
            }
            // NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
        }
    }

    return true;
}

} // namespace bitwise

namespace stl_bitset {

namespace detail {

[[nodiscard]] constexpr auto tick_out(auto const cell, auto& set) noexcept
    -> bool
{
    if (cell != decltype(cell){0})
    {
        if (not set.test(cell - 1U))
        {
            return false;
        }

        set.reset(cell - 1U);
    }

    return true;
}

} // namespace detail

template <typename CellType>
[[nodiscard]] constexpr auto
is_valid_sudoku(SudokuBoard<CellType> const& board) noexcept -> bool
{
    using SetType = std::bitset<9U>;

    static constexpr unsigned initval{0x1FF};

    // clang-format off
    std::array<SetType, 9U> rows{
        initval, initval, initval, initval, initval,
        initval, initval, initval, initval,
    };
    std::array<SetType, 9U> boxes{
        initval, initval, initval, initval, initval,
        initval, initval, initval, initval,
    };
    // clang-format on

    for (std::size_t i{}; i < board.size(); ++i)
    {
        SetType col{initval};

        for (std::size_t j{}; j < board.size(); ++j)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
            if (not detail::tick_out(board[i][j], col))
            {
                return false;
            }

            if (not detail::tick_out(board[j][i], rows[i]))
            {
                return false;
            }

            if (not detail::tick_out(
                    board[(3 * (i / 3)) + (j / 3)][(3 * (i % 3)) + (j % 3)],
                    boxes[i]
                ))
            {
                return false;
            }
            // NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
        }
    }

    return true;
}

} // namespace stl_bitset

} // namespace forfun::valid_sudoku

#endif // FORFUN_VALID_SUDOKU_HPP_
