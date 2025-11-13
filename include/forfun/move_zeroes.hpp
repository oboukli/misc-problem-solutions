// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/move-zeroes/

#ifndef FORFUN_MOVE_ZEROES_HPP_
#define FORFUN_MOVE_ZEROES_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>

namespace forfun::move_zeroes {

namespace sol1 {

template <std::sortable Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
constexpr auto move_zeroes(Iter iter, Sentinel const last) noexcept -> void
{
    using ValType = std::iter_value_t<Iter>;

    auto iter_j{iter};
    for (; iter != last; ++iter)
    {
        if (*iter != ValType{})
        {
            std::iter_swap(iter, iter_j);
            ++iter_j;
        }
    }
}

} // namespace sol1

namespace sol2 {

template <std::sortable Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
constexpr auto move_zeroes(Iter iter, Sentinel const last) noexcept -> void
{
    using ValType = std::iter_value_t<Iter>;

    auto iter_j{iter};
    for (; iter != last; ++iter)
    {
        if (*iter != ValType{})
        {
            *iter_j = *iter;
            ++iter_j;
        }
    }

    for (; iter_j != last; ++iter_j)
    {
        *iter_j = ValType{};
    }
}

} // namespace sol2

namespace stl {

template <std::sortable Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
constexpr auto move_zeroes(Iter iter, Sentinel const last) noexcept -> void
{
    using ValType = std::iter_value_t<Iter>;

    auto iter_j{iter};
    for (; iter != last; ++iter)
    {
        if (*iter != ValType{}) [[likely]]
        {
            *iter_j = *iter;
            ++iter_j;
        }
    }

    std::fill(iter_j, last, ValType{});
}

} // namespace stl

} // namespace forfun::move_zeroes

#endif // FORFUN_MOVE_ZEROES_HPP_
