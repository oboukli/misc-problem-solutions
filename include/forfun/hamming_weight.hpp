// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/number-of-1-bits/

#ifndef FORFUN_HAMMING_WEIGHT_HPP_
#define FORFUN_HAMMING_WEIGHT_HPP_

#include <algorithm>
#include <cstddef>
#include <limits>
#include <ranges>

namespace forfun::hamming_weight {

namespace linear_functional {

[[nodiscard]] constexpr auto get_hamming_weight(std::size_t const n) noexcept
    -> std::size_t
{
    return std::ranges::fold_left(
        std::views::iota(0UZ)
            | std::views::take(std::numeric_limits<std::size_t>::digits),
        0UZ,
        [n](std::size_t a, std::size_t b) noexcept -> std::size_t {
            return a + ((n >> b) & 1UZ);
        }
    );
}

} // namespace linear_functional

namespace linear_imperative {

[[nodiscard]] constexpr auto get_hamming_weight(std::size_t const n) noexcept
    -> std::size_t
{
    std::size_t result{0};
    for (std::size_t i{0}; i < std::numeric_limits<std::size_t>::digits; ++i)
    {
        result += (n >> i) & 1UZ;
    }

    return result;
}

} // namespace linear_imperative

namespace optimized_imperative {

[[nodiscard]] constexpr auto get_hamming_weight(std::size_t n) noexcept
    -> std::size_t
{
    std::size_t result{0};
    while (n != 0UZ)
    {
        n &= n - 1UZ;
        ++result;
    }

    return result;
}

} // namespace optimized_imperative

} // namespace forfun::hamming_weight

#endif // FORFUN_HAMMING_WEIGHT_HPP_
