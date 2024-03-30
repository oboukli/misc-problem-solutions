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

template <std::random_access_iterator RandomIt>
    requires std::integral<std::iter_value_t<RandomIt>>
constexpr void move_zeroes(RandomIt it, RandomIt const end) noexcept
{
    using ValType = std::iter_value_t<RandomIt>;

    auto it_j{it};
    for (; it != end; ++it)
    {
        if (*it != ValType{0})
        {
            std::iter_swap(it, it_j);
            ++it_j;
        }
    }
}

} // namespace sol1

namespace sol2 {

template <std::random_access_iterator RandomIt>
    requires std::integral<std::iter_value_t<RandomIt>>
constexpr void move_zeroes(RandomIt it, RandomIt const end) noexcept
{
    using ValType = std::iter_value_t<RandomIt>;

    auto it_j{it};
    for (; it != end; ++it)
    {
        if (*it != ValType{0})
        {
            *it_j = *it;
            ++it_j;
        }
    }

    for (; it_j != end; ++it_j)
    {
        *it_j = ValType{0};
    }
}

} // namespace sol2

namespace stl {

template <std::random_access_iterator RandomIt>
    requires std::integral<std::iter_value_t<RandomIt>>
constexpr void move_zeroes(RandomIt it, RandomIt const end) noexcept
{
    using ValType = std::iter_value_t<RandomIt>;

    auto it_j{it};
    for (; it != end; ++it)
    {
        if (*it != ValType{0})
        {
            *it_j = *it;
            ++it_j;
        }
    }

    std::fill(it_j, end, ValType{0});
}

} // namespace stl

} // namespace forfun::move_zeroes

#endif // FORFUN_MOVE_ZEROES_HPP_
