// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// - https://leetcode.com/problems/two-sum/
/// - https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
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
#include <functional>
#include <iterator>
#include <map>

namespace forfun::two_sum {

namespace brute_forced {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto two_sum(
    Iter iter, Sentinel const last, std::iter_value_t<Iter> const target
) noexcept -> std::array<Iter, 2UZ>
{
    for (; iter != last; ++iter)
    {
        auto const addend{std::minus{}(target, *iter)};

        for (auto iter_j{std::next(iter)}; iter_j != last; ++iter_j)
        {
            if (std::equal_to{}(*iter_j, addend))
            {
                return {iter, iter_j};
            }
        }
    }

    return {last, last};
}

} // namespace brute_forced

namespace mapped {

/// @note The strategy assumes that @p iter and @p last point to a non-empty
/// span of elements.
template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
two_sum(Iter iter, Sentinel const last, std::iter_value_t<Iter> const target)
    -> std::array<Iter, 2UZ>
{
    std::map<std::iter_value_t<Iter>, Iter> lookup_map{};
    lookup_map.emplace(*iter, iter);
    while (++iter != last)
    {
        auto const addend{std::minus{}(target, *iter)};

        if (auto const iter_found{lookup_map.find(addend)};
            iter_found != lookup_map.cend())
        {
            return {iter, iter_found->second};
        }

        lookup_map.emplace(*iter, iter);
    }

    return {last, last};
}

} // namespace mapped

namespace presorted_binary_searched {

/// @note The strategy assumes that @p iter and @p last point to a span of
/// elements sorted in non-decreasing order, and that the span has exactly one
/// solution.
template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto two_sum(
    Iter iter, Sentinel const last, std::iter_value_t<Iter> const target
) noexcept -> std::array<Iter, 2UZ>
{
    for (; iter != last; ++iter)
    {
        auto const addend{std::minus{}(target, *iter)};

        if (auto const iter_j{std::lower_bound(std::next(iter), last, addend)};
            iter_j != last)
        {
            return {iter, iter_j};
        }
    }

    return {last, last};
}

} // namespace presorted_binary_searched

namespace presorted_brute_searched {

/// @note The strategy assumes that @p iter and @p last point to a span of
/// elements sorted in non-decreasing order, and that the span has exactly one
/// solution.
template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto two_sum(
    Iter iter, Sentinel const last, std::iter_value_t<Iter> const target
) noexcept -> std::array<Iter, 2UZ>
{
    for (; iter != last; ++iter)
    {
        auto const addend{std::minus{}(target, *iter)};

        for (auto iter_j{std::next(iter)}; iter_j != last; ++iter_j)
        {
            if (std::equal_to{}(*iter_j, addend))
            {
                return {iter, iter_j};
            }

            if (std::greater{}(*iter, *iter_j))
            {
                break;
            }
        }
    }

    return {last, last};
}

} // namespace presorted_brute_searched

} // namespace forfun::two_sum

#endif // FORFUN_TWO_SUM_HPP_
