// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Binary_search_algorithm

#ifndef FORFUN_SEARCH_BINARY_SEARCH_HPP_
#define FORFUN_SEARCH_BINARY_SEARCH_HPP_

#include <iterator>

namespace forfun::search::binary_search {

namespace iterative {

template <std::random_access_iterator Itr, typename Target>
[[nodiscard]] constexpr auto
find(Itr lhs, Itr const last, Target const target) noexcept -> Itr
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

template <std::random_access_iterator Itr, typename Target>
[[nodiscard]] constexpr auto
do_find(Itr const first, Itr const last, Target const target) noexcept -> Itr
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

template <std::random_access_iterator Itr, typename Target>
[[nodiscard]] constexpr auto
find(Itr const first, Itr const last, Target const target) noexcept -> Itr
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
