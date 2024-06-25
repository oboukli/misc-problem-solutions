// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/set-matrix-zeroes/

#ifndef FORFUN_SET_MATRIX_ZEROES_HPP_
#define FORFUN_SET_MATRIX_ZEROES_HPP_

#include <vector>

namespace forfun::set_matrix_zeroes {

namespace offset_based {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void;

}

} // namespace forfun::set_matrix_zeroes

#endif // FORFUN_SET_MATRIX_ZEROES_HPP_
