// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Insertion_sort

#ifndef FORFUN_SORTING_INSERTION_SORT_HPP
#define FORFUN_SORTING_INSERTION_SORT_HPP

#include <algorithm>
#include <iterator>

namespace forfun::sorting {

template <std::bidirectional_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::sortable<Iter>
constexpr auto insertion_sort(Iter const first, Sentinel const last) noexcept
    -> void
{
    if (first != last) [[likely]]
    {
        for (Iter it_i{std::next(first)}; it_i != last; ++it_i)
        {
            // clang-format off
            for (Iter it_j{it_i};
                it_j != first && (*it_j < *std::prev(it_j)); --it_j)
            // clang-format on
            {
                std::iter_swap(it_j, std::prev(it_j));
            }
        }
    }
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_INSERTION_SORT_HPP
