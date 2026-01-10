// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/set_matrix_zeroes.hpp"

#include <cassert>
#include <vector>

namespace forfun::set_matrix_zeroes {

namespace iterator_based_sol1 {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void
{
    using DiffC = std::vector<std::vector<int>>::value_type::difference_type;

    if ((matrix.begin() == matrix.end()) || matrix.front().empty()) [[unlikely]]
    {
        return;
    }

    auto const first_element_iter{matrix.front().begin()};
    bool is_first_col_zeroed{false};

    for (auto row{matrix.begin()}; row != matrix.end(); ++row)
    {
        assert(matrix.front().size() == row->size());

        DiffC col_offset{};
        for (auto col{row->begin()}; col != row->end(); ++col)
        {
            if (*col == 0)
            {
                row->front() = 0;

                if (col_offset == DiffC{})
                {
                    is_first_col_zeroed = true;
                }
                else
                {
                    *(first_element_iter + col_offset) = 0;
                }
            }
            ++col_offset;
        }
    }

    // Zero all columns, except for the first one.
    for (auto row{matrix.begin()}; row != matrix.end(); ++row)
    {
        DiffC col_offset{1};
        // clang-format off
        for (auto col{row->begin() + col_offset}; col != row->end();
            ++col)
        // clang-format on
        {
            if (*(first_element_iter + col_offset) == 0)
            {
                *col = 0;
            }

            ++col_offset;
        }
    }

    // Zero all rows.
    for (auto row{matrix.begin()}; row != matrix.end(); ++row)
    {
        if (row->front() == 0)
        {
            for (auto col{row->begin()}; col != row->end(); ++col)
            {
                *col = 0;
            }
        }
    }

    if (is_first_col_zeroed)
    {
        // Zero first column.
        for (auto iter{matrix.begin()}; iter != matrix.end(); ++iter)
        {
            iter->front() = 0;
        }
    }
}

} // namespace iterator_based_sol1

namespace iterator_based_sol2 {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void
{
    using DiffC = std::vector<std::vector<int>>::value_type::difference_type;

    if ((matrix.begin() == matrix.end()) || matrix.begin()->empty())
        [[unlikely]]
    {
        return;
    }

    auto const front_iter{matrix.begin()->begin()};
    bool is_first_col_zeroed{false};

    for (auto row{matrix.begin()}; row != matrix.end(); ++row)
    {
        assert(matrix.front().size() == row->size());

        DiffC col_offset{};
        for (auto col{row->begin()}; col != row->end(); ++col)
        {
            if (*col == 0)
            {
                row->front() = 0;

                if (col_offset == DiffC{})
                {
                    is_first_col_zeroed = true;
                }
                else
                {
                    *(front_iter + col_offset) = 0;
                }
            }
            ++col_offset;
        }
    }

    // Zero all rows and columns, except for the first ones.
    for (auto row{matrix.begin() + 1}; row != matrix.end(); ++row)
    {
        DiffC col_offset{1};
        for (auto col{row->begin() + 1}; col != row->end(); ++col)
        {
            if ((*(front_iter + col_offset) == 0) || (row->front() == 0))
            {
                *col = 0;
            }

            ++col_offset;
        }
    }

    if (*front_iter == 0)
    {
        // Zero first row.
        for (auto col{front_iter + 1}; col != matrix.begin()->end(); ++col)
        {
            *col = 0;
        }
    }

    if (is_first_col_zeroed)
    {
        // Zero first column.
        for (auto iter{matrix.begin()}; iter != matrix.end(); ++iter)
        {
            iter->front() = 0;
        }
    }
}

} // namespace iterator_based_sol2

namespace offset_based {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void
{
    using MatrixR = std::vector<std::vector<int>>;
    using SizeTypeR = MatrixR::size_type;
    using SizeTypeC = MatrixR::value_type::size_type;

    auto const matrix_r_size{matrix.size()};

    if (matrix_r_size == SizeTypeR{}) [[unlikely]]
    {
        return;
    }

    auto const matrix_c_size{matrix.begin()->size()};

    if (matrix_c_size == SizeTypeC{}) [[unlikely]]
    {
        return;
    }

    bool is_col_zeroed{false};

    for (SizeTypeR row{}; row < matrix_r_size; ++row)
    {
        assert(matrix[row].size() == matrix_c_size);

        for (SizeTypeC col{}; col < matrix_c_size; ++col)
        {
            if (matrix[row][col] == 0)
            {
                matrix[row][0] = 0;
                if (col == 0)
                {
                    is_col_zeroed = true;
                    continue;
                }
                matrix[0][col] = 0;
            }
        }
    }

    for (SizeTypeR row{1}; row < matrix_r_size; ++row)
    {
        for (SizeTypeC col{1}; col < matrix_c_size; ++col)
        {
            if ((matrix[row][0] == 0) || (matrix[0][col] == 0))
            {
                matrix[row][col] = 0;
            }
        }
    }

    if (matrix[0][0] == 0)
    {
        for (SizeTypeC col{1}; col < matrix_c_size; ++col)
        {
            matrix[0][col] = 0;
        }
    }

    if (is_col_zeroed)
    {
        for (SizeTypeR row{}; row < matrix_r_size; ++row)
        {
            matrix[row][0] = 0;
        }
    }
}

} // namespace offset_based

} // namespace forfun::set_matrix_zeroes
