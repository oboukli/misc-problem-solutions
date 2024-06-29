// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Quicksort

#ifndef FORFUN_SORTING_QUICKSORT_HPP_
#define FORFUN_SORTING_QUICKSORT_HPP_

#include <algorithm>
#include <iterator>

namespace forfun::sorting {

template <std::contiguous_iterator Iter>
    requires std::sortable<Iter>
constexpr auto quicksort(Iter first, Iter last) noexcept -> void;

namespace detail {

template <std::contiguous_iterator Iter>
[[nodiscard]] constexpr auto
partition(Iter const first, Iter last) noexcept -> Iter
{
    auto it_i{first};

    {
        auto const pivot{*first};
        for (auto it_j{--last}; it_j != it_i;)
        {
            if (*it_j < pivot)
            {
                std::iter_swap(++it_i, it_j);
            }
            else
            {
                --it_j;
            }
        }
    }

    std::iter_swap(first, it_i);

    return it_i;
}

} // namespace detail

template <std::contiguous_iterator Iter>
    requires std::sortable<Iter>
constexpr auto quicksort(Iter const first, Iter const last) noexcept -> void
{
    using DiffType = std::iter_difference_t<Iter>;

    if ((last - first) < DiffType{2})
    {
        return;
    }

    auto p{detail::partition(first, last)};
    quicksort(first, p);
    quicksort(++p, last);
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_QUICKSORT_HPP_
