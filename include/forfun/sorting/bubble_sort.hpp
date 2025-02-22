// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Bubble_sort

#ifndef FORFUN_SORTING_BUBBLE_SORT_HPP_
#define FORFUN_SORTING_BUBBLE_SORT_HPP_

#include <algorithm>
#include <functional>
#include <iterator>

namespace forfun::sorting {

namespace plain {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// range of elements, otherwise the behavior of the strategy is undefined.
template <typename IterA, typename IterB>
    requires std::sortable<IterA>
    and std::bidirectional_iterator<IterA>
    and std::bidirectional_iterator<IterB>
auto bubble_sort(IterA const first, IterB last) noexcept -> void
{
    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    bool is_unsorted /*[[indeterminate]]*/;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        --last;
        is_unsorted = false;
        for (IterA it_i{first}; it_i != last; ++it_i)
        {
            auto it_ii{it_i};
            ++it_ii;
            if (*it_i > *it_ii)
            {
                auto const aux{*it_ii};
                *it_ii = *it_i;
                *it_i = aux;

                is_unsorted = true;
            }
        }
    } while (is_unsorted);
}

} // namespace plain

namespace stl {

/// @note The strategy assumes that @p first and @p last point to a non-empty
/// range of elements, otherwise the behavior of the strategy is undefined.
template <typename IterA, typename IterB>
    requires std::sortable<IterA>
    and std::bidirectional_iterator<IterA>
    and std::bidirectional_iterator<IterB>
auto bubble_sort(IterA const first, IterB last) noexcept -> void
{
    using std::greater;
    using std::iter_swap;
    using std::next;

    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    bool is_unsorted /*[[indeterminate]]*/;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        --last;
        is_unsorted = false;
        for (IterA it_i{first}; it_i != last; ++it_i)
        {
            if (greater{}(*it_i, *next(it_i)))
            {
                iter_swap(it_i, next(it_i));
                is_unsorted = true;
            }
        }
    } while (is_unsorted);
}

} // namespace stl

} // namespace forfun::sorting

#endif // FORFUN_SORTING_BUBBLE_SORT_HPP_
