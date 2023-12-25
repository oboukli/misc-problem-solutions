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
#include <type_traits>

namespace forfun::move_zeroes {

namespace sol1 {

template <
    typename RandomIt,
    typename ValTyp = std::iterator_traits<RandomIt>::value_type>
    requires std::random_access_iterator<RandomIt> && std::integral<ValTyp>
constexpr inline void move_zeroes(RandomIt it, RandomIt const end) noexcept
{
    auto it_j{it};
    for (; it != end; ++it)
    {
        if (*it != ValTyp{0})
        {
            std::iter_swap(it, it_j);
            ++it_j;
        }
    }
}

} // namespace sol1

namespace sol2 {

template <
    typename RandomIt,
    typename ValTyp = std::iterator_traits<RandomIt>::value_type>
    requires std::random_access_iterator<RandomIt> && std::integral<ValTyp>
constexpr inline void move_zeroes(RandomIt it, RandomIt const end) noexcept
{
    auto it_j{it};
    for (; it != end; ++it)
    {
        if (*it != ValTyp{0})
        {
            *it_j = *it;
            ++it_j;
        }
    }

    for (; it_j != end; ++it_j)
    {
        *it_j = ValTyp{0};
    }
}

} // namespace sol2

namespace stl {

template <
    typename RandomIt,
    typename ValTyp = std::iterator_traits<RandomIt>::value_type>
    requires std::random_access_iterator<RandomIt> && std::integral<ValTyp>
constexpr inline void move_zeroes(RandomIt it, RandomIt const end) noexcept
{
    auto it_j{it};
    for (; it != end; ++it)
    {
        if (*it != ValTyp{0})
        {
            *it_j = *it;
            ++it_j;
        }
    }

    std::fill(it_j, end, ValTyp{0});
}

} // namespace stl

} // namespace forfun::move_zeroes

#endif // FORFUN_MOVE_ZEROES_HPP_
