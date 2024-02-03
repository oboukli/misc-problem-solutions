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

namespace {

template <typename Iter>
    requires std::contiguous_iterator<Iter>
[[nodiscard]] constexpr inline auto
partition(Iter const first, Iter const last) noexcept
{
    auto const pivot_itr{first};
    auto const pivot{*pivot_itr};

    auto i{first};
    for (auto j{last - 1}; j != i;)
    {
        if (*j < pivot)
        {
            std::iter_swap(++i, j);
        }
        else
        {
            --j;
        }
    }

    std::iter_swap(pivot_itr, i);

    return i;
}

} // namespace

template <typename Iter>
    requires std::contiguous_iterator<Iter>
constexpr inline void quicksort(Iter const first, Iter const last) noexcept
{
    using DiffType = std::iter_difference_t<Iter>;

    if ((last - first) < DiffType{2})
    {
        return;
    }
    
    auto const p{partition(first, last)};
    quicksort(first, p);
    quicksort(p + 1, last);
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_QUICKSORT_HPP_
