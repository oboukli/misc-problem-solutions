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

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// range of elements, otherwise the behavior of the strategy is undefined.
template <typename Iter, typename Sentinel>
    requires std::sortable<Iter>
    and std::bidirectional_iterator<Iter>
    and std::sentinel_for<Iter, Sentinel>
auto insertion_sort(Iter const first, Sentinel const last) noexcept -> void
{
    using std::iter_swap;
    using std::less;
    using std::next;
    using std::prev;

    for (Iter it_i{next(first)}; it_i != last; ++it_i)
    {
        for (
            Iter it_j{it_i}; it_j != first && less{}(*it_j, *prev(it_j)); --it_j
        )
        {
            iter_swap(it_j, prev(it_j));
        }
    }
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_INSERTION_SORT_HPP
