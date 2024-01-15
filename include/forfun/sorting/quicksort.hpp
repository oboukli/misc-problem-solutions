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
partition(Iter const lo, Iter const hi) noexcept
{
    using Diff = std::iterator_traits<Iter>::difference_type;

    auto const pivot{*hi};

    auto i{lo - Diff{1}};
    for (auto j{lo}; j < hi; ++j)
    {
        if (*j < pivot)
        {
            ++i;
            std::iter_swap(i, j);
        }
    }

    ++i;
    std::iter_swap(hi, i);

    return i;
}

} // namespace

template <typename Iter>
    requires std::contiguous_iterator<Iter>
constexpr inline void quicksort(Iter const lo, Iter const hi) noexcept
{
    using Diff = std::iterator_traits<Iter>::difference_type;

    if (hi > lo)
    {
        auto const p{partition(lo, hi)};

        quicksort(lo, p - Diff{1});
        quicksort(p + Diff{1}, hi);
    }
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_QUICKSORT_HPP_
