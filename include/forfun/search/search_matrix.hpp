// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/search-a-2d-matrix/

#ifndef FORFUN_SEARCH_SEARCH_MATRIX_HPP_
#define FORFUN_SEARCH_SEARCH_MATRIX_HPP_

#include <vector>

namespace forfun::search::search_matrix {

namespace approach_a {

auto find(std::vector<std::vector<int>> const& matrix, int target) noexcept
    -> bool;

} // namespace approach_a

namespace approach_b {

auto find(std::vector<std::vector<int>> const& matrix, int target) noexcept
    -> bool;

} // namespace approach_b

} // namespace forfun::search::search_matrix

#endif // FORFUN_SEARCH_SEARCH_MATRIX_HPP_
