// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

#ifndef FORFUN_SEARCH_MINIMUM_ROTATED_ELEMENT_HPP_
#define FORFUN_SEARCH_MINIMUM_ROTATED_ELEMENT_HPP_

#include <concepts>
#include <functional>
#include <iterator>

namespace forfun::search::minimum_rotated_element {

namespace iterative {

/// @note Assumes that @p first and @p last point to a non-empty span of unique
/// elements sorted in ascending order, otherwise the behavior of the strategy
/// is undefined.
template <typename Iter, typename Sentinel>
    requires std::bidirectional_iterator<Iter>
    and std::sized_sentinel_for<Iter, Sentinel>
    and std::totally_ordered<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto find_min(Iter first, Sentinel const last) noexcept
    -> Iter
{
    using std::distance;
    using std::less;
    using std::next;
    using std::prev;

    auto rhs{prev(last)};

    while (first != rhs)
    {
        auto const mid{next(first, distance(first, rhs) / 2)};

        if (less{}(*mid, *rhs))
        {
            rhs = mid;
        }
        else
        {
            first = next(mid);
        }
    }

    return first;
}

} // namespace iterative

namespace recursive {

/// @note Assumes that @p first and @p last point to a non-empty span of unique
/// elements sorted in ascending order, otherwise the behavior of the strategy
/// is undefined.
template <typename Iter, typename Sentinel>
    requires std::bidirectional_iterator<Iter>
    and std::sized_sentinel_for<Iter, Sentinel>
    and std::totally_ordered<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto find_min(Iter first, Sentinel const last) noexcept
    -> Iter
{
    using std::distance;
    using std::less;
    using std::next;
    using std::prev;

    if (auto rhs{prev(last)}; less{}(*rhs, *first))
    {
        auto const mid{next(first, distance(first, last) / 2)};

        first = find_min(first, mid);
        rhs = find_min(mid, last);
        if (less{}(*rhs, *first))
        {
            return rhs;
        }
    }

    return first;
}

} // namespace recursive

} // namespace forfun::search::minimum_rotated_element

#endif // FORFUN_SEARCH_MINIMUM_ROTATED_ELEMENT_HPP_
