// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/set_matrix_zeroes.hpp"

#include <cassert>
#include <vector>

namespace forfun::set_matrix_zeroes {

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
