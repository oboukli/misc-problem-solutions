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

template <std::contiguous_iterator Iter>
[[nodiscard]] constexpr inline Iter
partition(Iter const first, Iter const last) noexcept
{
    auto i{first};

    {
        using DiffType = std::iter_difference_t<Iter>;

        auto const pivot{*first};
        for (auto j{last - DiffType{1}}; j != i;)
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
    }

    std::iter_swap(first, i);

    return i;
}

} // namespace

template <std::contiguous_iterator Iter>
constexpr inline void quicksort(Iter const first, Iter const last) noexcept
{
    using DiffType = std::iter_difference_t<Iter>;

    if ((last - first) < DiffType{2})
    {
        return;
    }

    auto const p{partition(first, last)};
    quicksort(first, p);
    quicksort(p + DiffType{1}, last);
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_QUICKSORT_HPP_
