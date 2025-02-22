// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Quicksort

#ifndef FORFUN_SORTING_QUICKSORT_HPP_
#define FORFUN_SORTING_QUICKSORT_HPP_

#include <algorithm>
#include <functional>
#include <iterator>

namespace forfun::sorting {

namespace detail {

template <typename IterA, typename IterB>
    requires std::sortable<IterA>
    and std::bidirectional_iterator<IterA>
    and std::bidirectional_iterator<IterB>
[[nodiscard]] constexpr auto partition(IterA const first, IterB last) noexcept
    -> IterA
{
    using std::iter_swap;
    using std::less;

    auto it_i{first};

    auto const pivot{*first};
    for (auto it_j{--last}; it_j != it_i;)
    {
        if (less{}(*it_j, pivot))
        {
            iter_swap(++it_i, it_j);
        }
        else
        {
            --it_j;
        }
    }

    iter_swap(first, it_i);

    return it_i;
}

} // namespace detail

template <typename IterA, typename IterB>
    requires std::sortable<IterA>
    and std::bidirectional_iterator<IterA>
    and std::bidirectional_iterator<IterB>
constexpr auto quicksort(IterA const first, IterB const last) noexcept -> void
{
    using std::distance;
    using std::less;

    using DiffType = std::iter_difference_t<IterA>;

    if (less{}(distance(first, last), DiffType{2}))
    {
        return;
    }

    auto partition{detail::partition(first, last)};
    quicksort(first, partition);
    quicksort(++partition, last);
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_QUICKSORT_HPP_
