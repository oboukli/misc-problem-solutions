// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Insertion_sort

#ifndef FORFUN_SORTING_INSERTION_SORT_HPP
#define FORFUN_SORTING_INSERTION_SORT_HPP

#include <algorithm>
#include <iterator>

namespace forfun::sorting {

template <std::contiguous_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::sortable<Iter>
constexpr auto insertion_sort(Iter const begin, Sentinel const end) noexcept
    -> void
{
    using DiffType = std::iter_difference_t<Iter>;

    if (begin != end) [[likely]]
    {
        for (Iter it_i{begin + DiffType{1}}; it_i != end; ++it_i)
        {
            // clang-format off
            for (Iter it_j{it_i};
                it_j != begin && (*it_j < *(it_j - DiffType{1})); --it_j)
            // clang-format on
            {
                std::iter_swap(it_j, it_j - DiffType{1});
            }
        }
    }
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_INSERTION_SORT_HPP
