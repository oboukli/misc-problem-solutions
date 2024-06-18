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

    auto const matrix_begin{matrix.begin()};
    auto const matrix_end{matrix.end()};

    if (matrix_begin == matrix_end)
    {
        return;
    }

    if (matrix_begin->size() == 0)
    {
        return;
    }

    auto const first_element_itr{matrix_begin->begin()};
    bool is_first_col_zeroed{false};

    for (auto itr_r{matrix_begin}; itr_r != matrix_end; ++itr_r)
    {
        assert(matrix_begin->size() == itr_r->size());

        auto const itr_c_begin{itr_r->begin()};
        auto const itr_c_end{itr_r->end()};
        DiffC col_offset{0};
        for (auto itr_c{itr_c_begin}; itr_c != itr_c_end; ++itr_c)
        {
            if (*itr_c == 0)
            {
                *itr_c_begin = 0;

                if (col_offset == 0)
                {
                    is_first_col_zeroed = true;
                }
                else
                {
                    *(first_element_itr + col_offset) = 0;
                }
            }
            ++col_offset;
        }
    }

    // Zero all columns, except for the first one.
    for (auto itr_r{matrix_begin}; itr_r != matrix_end; ++itr_r)
    {
        auto const itr_c_end{itr_r->end()};
        DiffC col_offset{1};
        // clang-format off
        for (auto itr_c{itr_r->begin() + col_offset}; itr_c != itr_c_end;
            ++itr_c)
        // clang-format on
        {
            if (*(first_element_itr + col_offset) == 0)
            {
                *itr_c = 0;
            }

            ++col_offset;
        }
    }

    // Zero all rows.
    for (auto itr_r{matrix_begin}; itr_r != matrix_end; ++itr_r)
    {
        if (itr_r->front() == 0)
        {
            auto const itr_c_end{itr_r->end()};
            for (auto itr_c{itr_r->begin()}; itr_c != itr_c_end; ++itr_c)
            {
                *itr_c = 0;
            }
        }
    }

    if (is_first_col_zeroed)
    {
        // Zero first column.
        for (auto itr{matrix_begin}; itr != matrix_end; ++itr)
        {
            *itr->begin() = 0;
        }
    }
}

} // namespace iterator_based_sol1


namespace offset_based {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void
{
    using MatrixR = std::vector<std::vector<int>>;
    using SizeTypeR = MatrixR::size_type;
    using SizeTypeC = MatrixR::value_type::size_type;

    auto const matrix_r_size{matrix.size()};

    if (matrix_r_size == 0)
    {
        return;
    }

    auto const matrix_c_size{matrix.begin()->size()};

    if (matrix_c_size == 0)
    {
        return;
    }

    bool is_col_zeroed{false};

    for (SizeTypeR r{0}; r < matrix_r_size; ++r)
    {
        assert(matrix[r].size() == matrix_c_size);

        for (SizeTypeC c{0}; c < matrix_c_size; ++c)
        {
            if (matrix[r][c] == 0)
            {
                matrix[r][0] = 0;
                if (c == 0)
                {
                    is_col_zeroed = true;
                    continue;
                }
                matrix[0][c] = 0;
            }
        }
    }

    for (SizeTypeR r{1}; r < matrix_r_size; ++r)
    {
        for (SizeTypeC c{1}; c < matrix_c_size; ++c)
        {
            if ((matrix[r][0] == 0) || (matrix[0][c] == 0))
            {
                matrix[r][c] = 0;
            }
        }
    }

    if (matrix[0][0] == 0)
    {
        for (SizeTypeC c{1}; c < matrix_c_size; ++c)
        {
            matrix[0][c] = 0;
        }
    }

    if (is_col_zeroed)
    {
        for (SizeTypeR r{0}; r < matrix_r_size; ++r)
        {
            matrix[r][0] = 0;
        }
    }
}

} // namespace offset_based

} // namespace forfun::set_matrix_zeroes
