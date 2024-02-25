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
#include <iterator>

namespace forfun::two_sum {

template <std::random_access_iterator RandomIt>
[[nodiscard]] constexpr inline std::array<std::iter_difference_t<RandomIt>, 2>
two_sum(
    RandomIt const first,
    RandomIt const end,
    std::iter_value_t<RandomIt> const target) noexcept
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

    using DiffType = std::iter_difference_t<RandomIt>;

    return {DiffType{-1}, DiffType{-1}};
}

} // namespace forfun::two_sum

#endif // FORFUN_TWO_SUM_HPP_
