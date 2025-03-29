// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/set-matrix-zeroes/

#ifndef FORFUN_SET_MATRIX_ZEROES_HPP_
#define FORFUN_SET_MATRIX_ZEROES_HPP_

#include <vector>

namespace forfun::set_matrix_zeroes {

namespace iterator_based_sol1 {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void;

} // namespace iterator_based_sol1

namespace iterator_based_sol2 {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void;

} // namespace iterator_based_sol2

namespace offset_based {

auto set_zeroes(std::vector<std::vector<int>>& matrix) noexcept -> void;

} // namespace offset_based

} // namespace forfun::set_matrix_zeroes

#endif // FORFUN_SET_MATRIX_ZEROES_HPP_
