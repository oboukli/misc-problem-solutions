// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/missing-number/

#ifndef FORFUN_MISSING_NUMBER_HPP_
#define FORFUN_MISSING_NUMBER_HPP_

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <functional>
#include <iterator>
#include <ranges>

namespace forfun::missing_number {

namespace bitwise {

template <std::ranges::input_range Range>
    requires std::ranges::sized_range<Range>
    and std::integral<std::ranges::range_value_t<Range>>
[[nodiscard]] constexpr auto find_missing_number(Range&& range) noexcept
    -> std::ranges::range_value_t<Range>
{
    // Adopted from
    // https://github.com/walkccc/LeetCode/blob/main/solutions/268.%20Missing%20Number/268.cpp
    std::size_t acc{std::ranges::size(range)};
    std::size_t i{};
    for (auto&& val : std::forward<Range>(range))
    {
        acc ^= static_cast<std::size_t>(val) ^ i++;
    }

    return static_cast<std::ranges::range_value_t<Range>>(acc);
}

} // namespace bitwise

namespace functional {

template <std::ranges::input_range Range>
    requires std::ranges::sized_range<Range>
    and std::integral<std::ranges::range_value_t<Range>>
[[nodiscard]] constexpr auto find_missing_number(Range&& range) noexcept
    -> std::ranges::range_value_t<Range>
{
    auto const n{std::ranges::size(range)};

    auto sum{static_cast<std::ranges::range_value_t<Range>>(((n * n) + n) / 2)};

    return std::ranges::fold_left(
        std::forward<Range>(range), sum, std::minus{}
    );
}

} // namespace functional

namespace imperative {

template <std::ranges::input_range Range>
    requires std::ranges::sized_range<Range>
    and std::integral<std::ranges::range_value_t<Range>>
[[nodiscard]] constexpr auto find_missing_number(Range&& range) noexcept
    -> std::ranges::range_value_t<Range>
{
    auto const n{std::ranges::size(range)};

    auto sum{static_cast<std::ranges::range_value_t<Range>>(((n * n) + n) / 2)};

    for (auto&& val : std::forward<Range>(range))
    {
        sum -= val;
    }

    return sum;
}

} // namespace imperative

} // namespace forfun::missing_number

#endif // FORFUN_MISSING_NUMBER_HPP_
