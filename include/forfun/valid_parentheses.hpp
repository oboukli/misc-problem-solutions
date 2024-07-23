// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/valid-parentheses/description/

#ifndef FORFUN_VALID_PARENTHESES_HPP_
#define FORFUN_VALID_PARENTHESES_HPP_

#include <string_view>

namespace forfun::valid_parentheses {

namespace ascii_optimized {

[[nodiscard]] auto is_valid(std::u8string_view s) noexcept -> bool;

} // namespace ascii_optimized

namespace circuit_breaker {

[[nodiscard]] auto is_valid(std::u8string_view s) noexcept -> bool;

} // namespace circuit_breaker

namespace deque_based {

[[nodiscard]] auto is_valid(std::u8string_view s) noexcept -> bool;

} // namespace deque_based

namespace dyn_array_based {

[[nodiscard]] auto is_valid(std::u8string_view s) noexcept -> bool;

} // namespace dyn_array_based

namespace vector_based {

[[nodiscard]] auto is_valid(std::u8string_view s) noexcept -> bool;

} // namespace vector_based

namespace vector_based_demi_allocated {

[[nodiscard]] auto is_valid(std::u8string_view s) noexcept -> bool;

} // namespace vector_based_demi_allocated

} // namespace forfun::valid_parentheses

#endif // FORFUN_VALID_PARENTHESES_HPP_
