// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/two-sum/
/// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
///
/// Original problem text:
/// Given an array of integers nums and an integer target, return indices of the
/// two numbers such that they add up to target. You may assume that each input
/// would have exactly one solution, and you may not use the same element twice.
/// You can return the answer in any order.

#ifndef FORFUN_TWO_SUM_HPP_
#define FORFUN_TWO_SUM_HPP_

#include <algorithm>
#include <array>
#include <concepts>
#include <iterator>
#include <map>

namespace forfun::two_sum {

namespace brute_force {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto two_sum(
    Iter iter, Sentinel const end, std::iter_value_t<Iter> const target
) noexcept -> std::array<Iter, 2U>
{
    for (; iter != end; ++iter)
    {
        decltype(target) const addend{target - *iter};

        for (auto itr_j{std::next(iter)}; itr_j != end; ++itr_j)
        {
            if (*itr_j == addend)
            {
                return {iter, itr_j};
            }
        }
    }

    return {end, end};
}

} // namespace brute_force

namespace map_based {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto two_sum(
    Iter const first, Sentinel const end, std::iter_value_t<Iter> const target
) -> std::array<Iter, 2U>
{
    std::map<std::iter_value_t<Iter>, Iter> lookup_map{};
    for (auto iter{first}; iter != end; ++iter)
    {
        lookup_map.insert({*iter, iter});
    }

    for (auto iter{first}; iter != end; ++iter)
    {
        auto const addend{target - *iter};

        if (auto const found_iter{lookup_map.find(addend)};
            (found_iter != lookup_map.cend()) && (found_iter->second != iter))
        {
            return {iter, found_iter->second};
        }
    }

    return {end, end};
}

} // namespace map_based

namespace presorted {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
two_sum(Iter iter, Sentinel const end, std::iter_value_t<Iter> const target)
    -> std::array<Iter, 2U>
{
    for (; iter != end; ++iter)
    {
        decltype(target) const addend{target - (*iter)};

        if (auto const iter_j{std::lower_bound(std::next(iter), end, addend)};
            iter_j != end)
        {
            return {iter, iter_j};
        }
    }

    return {end, end};
}

} // namespace presorted

} // namespace forfun::two_sum

#endif // FORFUN_TWO_SUM_HPP_
