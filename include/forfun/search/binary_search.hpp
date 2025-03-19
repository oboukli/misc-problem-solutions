// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Binary_search_algorithm

#ifndef FORFUN_SEARCH_BINARY_SEARCH_HPP_
#define FORFUN_SEARCH_BINARY_SEARCH_HPP_

#include <concepts>
#include <iterator>

namespace forfun::search::binary_search {

namespace iterative {

/// @warning The strategy assumes that the iterator and its sentinel point to a
/// container of elements sorted in non-descending order, otherwise the behavior
/// of the strategy is undefined.
template <
    std::forward_iterator Itr,
    std::sized_sentinel_for<Itr> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Itr>> Target>
[[nodiscard]] constexpr auto
find(Itr lhs, Sentinel const last, Target const target) noexcept -> Itr
{
    using DiffType = std::iter_difference_t<Itr>;

    for (Itr rhs{last}; lhs != rhs;)
    {
        auto const distance{std::distance(lhs, rhs)};
        Itr mid{std::next(lhs, distance / DiffType{2})};
        if (target < *mid)
        {
            rhs = mid;
        }
        else if (target > *mid)
        {
            std::advance(mid, distance % DiffType{2});
            lhs = mid;
        }
        else
        {
            return mid;
        }
    }

    return last;
}

} // namespace iterative

namespace recursive {

namespace detail {

template <
    std::forward_iterator Itr,
    std::sized_sentinel_for<Itr> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Itr>> Target>
[[nodiscard]] constexpr auto
do_find(Itr const first, Sentinel const last, Target const target) noexcept
    -> Itr
{
    using DiffType = std::iter_difference_t<Itr>;

    auto const distance{std::distance(first, last)};
    if (distance < DiffType{1})
    {
        return last;
    }

    Itr mid{std::next(first, distance / DiffType{2})};
    if (target < *mid)
    {
        return do_find(first, mid, target);
    }

    if (target > *mid)
    {
        std::advance(mid, distance % DiffType{2});

        return do_find(mid, last, target);
    }

    return mid;
}

} // namespace detail

/// @warning The strategy assumes that the iterator and its sentinel point to a
/// container of elements sorted in non-descending order, otherwise the behavior
/// of the strategy is undefined.
template <
    std::forward_iterator Itr,
    std::sized_sentinel_for<Itr> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Itr>> Target>
[[nodiscard]] constexpr auto
find(Itr const first, Sentinel const last, Target const target) noexcept -> Itr
{
    if (Itr const itr{detail::do_find(first, last, target)};
        (itr != last) && (*itr == target))
    {
        return itr;
    }

    return last;
}

} // namespace recursive

} // namespace forfun::search::binary_search

#endif // FORFUN_SEARCH_BINARY_SEARCH_HPP_
