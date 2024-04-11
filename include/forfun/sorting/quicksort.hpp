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

namespace detail {

template <std::contiguous_iterator Iter>
[[nodiscard]] constexpr auto
partition(Iter const first, Iter const last) noexcept -> Iter
{
    auto it_i{first};

    {
        using DiffType = std::iter_difference_t<Iter>;

        auto const pivot{*first};
        for (auto it_j{last - DiffType{1}}; it_j != it_i;)
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
constexpr auto quicksort(Iter const first, Iter const last) noexcept -> void
{
    using DiffType = std::iter_difference_t<Iter>;

    if ((last - first) < DiffType{2})
    {
        return;
    }

    auto const p{detail::partition(first, last)};
    quicksort(first, p);
    quicksort(p + DiffType{1}, last);
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_QUICKSORT_HPP_
