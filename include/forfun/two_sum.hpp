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

template <std::input_iterator InputItr, std::sentinel_for<InputItr> Sentinel>
[[nodiscard]] constexpr auto two_sum(
    InputItr itr, Sentinel const end, std::iter_value_t<InputItr> const target
) noexcept -> std::array<InputItr, 2U>
{
    for (; itr != end; ++itr)
    {
        auto const t{target - (*itr)};

        auto itr_j{itr};
        for (++itr_j; itr_j != end; ++itr_j)
        {
            if ((*itr_j) == t)
            {
                return {itr, itr_j};
            }
        }
    }

    return {end, end};
}

} // namespace forfun::two_sum

#endif // FORFUN_TWO_SUM_HPP_
