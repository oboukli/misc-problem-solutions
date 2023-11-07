// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/two-sum/
///
/// Original problem text:
/// Given an array of integers nums and an integer target, return indices of the
/// two numbers such that they add up to target. You may assume that each input
/// would have exactly one solution, and you may not use the same element twice.
/// You can return the answer in any order.

#ifndef FORFUN_TWO_SUM_HPP_
#define FORFUN_TWO_SUM_HPP_

#include <array>
#include <concepts>
#include <iterator>

namespace forfun::two_sum {

template <
    typename RandomIt,
    typename T,
    typename Diff = std::iterator_traits<RandomIt>::difference_type>
    requires std::random_access_iterator<RandomIt> && std::integral<T>
[[nodiscard]] constexpr inline std::array<Diff, 2>
two_sum(RandomIt const first, RandomIt const end, T const target) noexcept
{
    for (auto it_i{first}; it_i != end; ++it_i)
    {
        auto const t{target - (*it_i)};

        for (auto it_j{it_i + 1}; it_j != end; ++it_j)
        {
            if ((*it_j) == t)
            {
                return {it_i - first, it_j - first};
            }
        }
    }

    return {Diff{-1}, Diff{-1}};
}

} // namespace forfun::two_sum

#endif // FORFUN_TWO_SUM_HPP_
