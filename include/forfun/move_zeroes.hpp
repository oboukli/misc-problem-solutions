// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/move-zeroes/

#ifndef FORFUN_MOVE_ZEROES_HPP_
#define FORFUN_MOVE_ZEROES_HPP_

#include <algorithm>
#include <concepts>
#include <iterator>

namespace forfun::move_zeroes {

namespace sol1 {

template <std::sortable Itr, std::sentinel_for<Itr> Sentinel>
    requires std::integral<std::iter_value_t<Itr>>
constexpr auto move_zeroes(Itr itr, Sentinel const end) noexcept -> void
{
    using ValType = std::iter_value_t<Itr>;

    auto itr_j{itr};
    for (; itr != end; ++itr)
    {
        if (*itr != ValType{0}) [[likely]]
        {
            std::iter_swap(itr, itr_j);
            ++itr_j;
        }
    }
}

} // namespace sol1

namespace sol2 {

template <std::sortable Itr, std::sentinel_for<Itr> Sentinel>
    requires std::integral<std::iter_value_t<Itr>>
constexpr auto move_zeroes(Itr itr, Sentinel const end) noexcept -> void
{
    using ValType = std::iter_value_t<Itr>;

    auto itr_j{itr};
    for (; itr != end; ++itr)
    {
        if (*itr != ValType{0}) [[likely]]
        {
            *itr_j = *itr;
            ++itr_j;
        }
    }

    for (; itr_j != end; ++itr_j)
    {
        *itr_j = ValType{0};
    }
}

} // namespace sol2

namespace stl {

template <std::sortable Itr, std::sentinel_for<Itr> Sentinel>
    requires std::integral<std::iter_value_t<Itr>>
constexpr auto move_zeroes(Itr itr, Sentinel const end) noexcept -> void
{
    using ValType = std::iter_value_t<Itr>;

    auto itr_j{itr};
    for (; itr != end; ++itr)
    {
        if (*itr != ValType{0}) [[likely]]
        {
            *itr_j = *itr;
            ++itr_j;
        }
    }

    std::fill(itr_j, end, ValType{0});
}

} // namespace stl

} // namespace forfun::move_zeroes

#endif // FORFUN_MOVE_ZEROES_HPP_
