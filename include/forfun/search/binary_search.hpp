// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Binary_search_algorithm

#ifndef FORFUN_SEARCH_BINARY_SEARCH_HPP_
#define FORFUN_SEARCH_BINARY_SEARCH_HPP_

#include <concepts>
#include <iterator>

namespace forfun::search::binary_search {

namespace iterative {

/// @note The strategy assumes that @p lhs and @p last point to a span of
/// elements sorted in non-descending order, otherwise the behavior of the
/// strategy is undefined.
template <
    std::forward_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Iter>> Target>
    requires std::forward_iterator<Sentinel>
[[nodiscard]] constexpr auto
find(Iter lhs, Sentinel const last, Target const target) noexcept -> Iter
{
    using DiffType = std::iter_difference_t<Iter>;

    for (Iter rhs{last}; lhs != rhs;)
    {
        auto const distance{std::distance(lhs, rhs)};
        Iter mid{std::next(lhs, distance / DiffType{2})};
        if (target < *mid)
        {
            rhs = mid;
        }
        else if (target > *mid)
        {
            std::advance(
                lhs, (distance / DiffType{2}) + (distance % DiffType{2})
            );
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
    std::forward_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Iter>> Target>
[[nodiscard]] constexpr auto
do_find(Iter const first, Sentinel const last, Target const target) noexcept
    -> Iter
{
    using DiffType = std::iter_difference_t<Iter>;

    auto const distance{std::distance(first, last)};
    if (distance < DiffType{1})
    {
        return last;
    }

    Iter mid{std::next(first, distance / DiffType{2})};
    if (target < *mid)
    {
        return do_find(first, mid, target);
    }

    if (target > *mid)
    {
        return do_find(std::next(mid), last, target);
    }

    return mid;
}

} // namespace detail

/// @note The strategy assumes that @p first and @p last point to a span of
/// elements sorted in non-descending order, otherwise the behavior of the
/// strategy is undefined.
template <
    std::forward_iterator Iter,
    std::sized_sentinel_for<Iter> Sentinel,
    std::totally_ordered_with<std::iter_value_t<Iter>> Target>
[[nodiscard]] constexpr auto
find(Iter const first, Sentinel const last, Target const target) noexcept
    -> Iter
{
    if (Iter const iter{detail::do_find(first, last, target)};
        (iter != last) && (*iter == target))
    {
        return iter;
    }

    return last;
}

} // namespace recursive

} // namespace forfun::search::binary_search

#endif // FORFUN_SEARCH_BINARY_SEARCH_HPP_
