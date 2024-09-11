// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/add-two-numbers/description/

#ifndef FORFUN_ADD_TWO_NUMBERS_HPP_
#define FORFUN_ADD_TWO_NUMBERS_HPP_

#include <forward_list>

namespace forfun::add_two_numbers::stl {

[[nodiscard]] auto add_two_numbers(
    std::forward_list<unsigned int> const& addend_a,
    std::forward_list<unsigned int> const& addend_b
) noexcept -> std::forward_list<unsigned int>;

} // namespace forfun::add_two_numbers::stl

#endif // FORFUN_ADD_TWO_NUMBERS_HPP_
