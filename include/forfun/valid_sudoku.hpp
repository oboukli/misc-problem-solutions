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
#include <functional>

namespace forfun::valid_sudoku {

template <typename CellType>
    requires std::integral<CellType>
using SudokuBoard = std::array<std::array<CellType, 9>, 9>;

namespace bitwise {

namespace detail {

template <typename Cell>
    requires std::unsigned_integral<Cell>
[[nodiscard]] constexpr auto tick_out(Cell const cell, auto& set) noexcept
    -> bool
{
    if (cell != decltype(cell){})
    {
        if (((1U << (cell - 1U)) & set) != 0U)
        {
            return true;
        }

        set |= (1U << (cell - 1U));
    }

    return false;
}

} // namespace detail

template <typename CellType>
[[nodiscard]] constexpr auto
is_valid_sudoku(SudokuBoard<CellType> const& board) noexcept -> bool
{
    using std::size;

    using SetType = unsigned int;

    std::array<SetType, 9> rows{};
    std::array<SetType, 9> boxes{};

    for (std::size_t i{}; i < size(board); ++i)
    {
        SetType col{};

        for (std::size_t j{}; j < size(board); ++j)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
            if (detail::tick_out(board[i][j], col))
            {
                return false;
            }

            if (detail::tick_out(board[j][i], rows[i]))
            {
                return false;
            }

            if (detail::tick_out(
                    board[(3UZ * (i / 3UZ)) + (j / 3UZ)]
                         [(3UZ * (i % 3UZ)) + (j % 3UZ)],
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

template <typename Cell>
    requires std::unsigned_integral<Cell>
[[nodiscard]] constexpr auto tick_out(Cell const cell, auto& set) noexcept
    -> bool
{
    if (cell != decltype(cell){})
    {
        if (set.test(cell - 1U))
        {
            return true;
        }

        set.set(cell - 1U);
    }

    return false;
}

} // namespace detail

template <typename CellType>
[[nodiscard]] constexpr auto
is_valid_sudoku(SudokuBoard<CellType> const& board) noexcept -> bool
{
    using std::divides;
    using std::modulus;
    using std::multiplies;
    using std::plus;

    using SetType = std::bitset<9>;

    std::array<SetType, 9> rows{};
    std::array<SetType, 9> boxes{};

    for (std::size_t i{}; i < size(board); ++i)
    {
        SetType col{};

        for (std::size_t j{}; j < size(board); ++j)
        {
            // NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
            if (detail::tick_out(board[i][j], col))
            {
                return false;
            }

            if (detail::tick_out(board[j][i], rows[i]))
            {
                return false;
            }

            if (
                // clang-format off
                detail::tick_out(
                    board
                        [plus{}(
                            multiplies{}(3UZ, divides{}(i, 3UZ)),
                            divides{}(j, 3UZ)
                        )]
                        [plus{}(
                            multiplies{}(3UZ, modulus{}(i, 3UZ)),
                            modulus{}(j, 3UZ)
                        )],
                    boxes[i]
                )
                // clang-format on
            )
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
