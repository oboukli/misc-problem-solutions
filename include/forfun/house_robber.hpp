// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/house-robber/

#ifndef FORFUN_HOUSE_ROBBER_HPP_
#define FORFUN_HOUSE_ROBBER_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>

namespace forfun::house_robber::recursive {

template <std::forward_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::same_as<int, std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto rob(Iter const first, Sentinel const last) noexcept
{
    using DiffType = std::iter_difference_t<Iter>;

    auto const size{std::distance(first, last)};
    if (size == DiffType{0}) [[unlikely]]
    {
        return 0;
    }

    if (size == DiffType{1}) [[unlikely]]
    {
        return *first;
    }

    if (size == DiffType{2}) [[unlikely]]
    {
        return std::max(*first, *(std::next(first)));
    }

    return std::max(
        (*first) + rob(std::next(first, DiffType{2}), last),
        *(std::next(first)) + rob(std::next(first, DiffType{3}), last)
    );
}

} // namespace forfun::house_robber::recursive

#endif // FORFUN_HOUSE_ROBBER_HPP_
