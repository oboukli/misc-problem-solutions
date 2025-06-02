// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/single-number/

#ifndef FORFUN_SINGLE_NUMBER_HPP_
#define FORFUN_SINGLE_NUMBER_HPP_

#include <algorithm>
#include <concepts>
#include <functional>
#include <ranges>

namespace forfun::single_number {

namespace imperative {

template <std::ranges::input_range Range>
    requires std::integral<std::ranges::range_value_t<Range>>
[[nodiscard]] constexpr auto get_single(Range&& nums) noexcept
    -> std::ranges::range_value_t<Range>
{
    std::ranges::range_value_t<Range> result{0};

    for (auto const n : std::forward<Range>(nums))
    {
        // NOLINTNEXTLINE(hicpp-signed-bitwise)
        result ^= n;
    }

    return result;
}

} // namespace imperative

namespace functional {

template <std::ranges::input_range Range>
    requires std::integral<std::ranges::range_value_t<Range>>
[[nodiscard]] constexpr auto get_single(Range&& nums) noexcept
    -> std::ranges::range_value_t<Range>
{
    return std::ranges::fold_left(
        std::forward<Range>(nums),
        std::ranges::range_value_t<Range>{0},
        std::bit_xor{}
    );
}

} // namespace functional

} // namespace forfun::single_number

#endif // FORFUN_SINGLE_NUMBER_HPP_
