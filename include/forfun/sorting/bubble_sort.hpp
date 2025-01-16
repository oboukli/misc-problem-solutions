// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Bubble_sort

#ifndef FORFUN_SORTING_BUBBLE_SORT_HPP_
#define FORFUN_SORTING_BUBBLE_SORT_HPP_

#include <algorithm>
#include <iterator>

namespace forfun::sorting {

namespace plain {

template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::sortable<Iter>
constexpr auto bubble_sort(Iter const begin, Sentinel end) noexcept -> void
{
    if (begin == end) [[unlikely]]
    {
        return;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    bool f /*[[indeterminate]]*/;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        --end;
        f = false;
        for (Iter it_i{begin}; it_i != end; ++it_i)
        {
            auto const it_ii{it_i + std::iter_difference_t<Iter>{1}};
            if (*it_i > *it_ii)
            {
                auto const aux{*it_ii};
                *it_ii = *it_i;
                *it_i = aux;

                f = true;
            }
        }
    } while (f);
}

} // namespace plain

namespace stl {

template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::sortable<Iter>
constexpr auto bubble_sort(Iter const begin, Sentinel end) noexcept -> void
{
    using DiffType = std::iter_difference_t<Iter>;

    if (begin == end) [[unlikely]]
    {
        return;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    bool f /*[[indeterminate]]*/;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        --end;
        f = false;
        for (Iter it_i{begin}; it_i != end; ++it_i)
        {
            if (*it_i > *(it_i + DiffType{1}))
            {
                std::iter_swap(it_i, it_i + DiffType{1});
                f = true;
            }
        }
    } while (f);
}

} // namespace stl

} // namespace forfun::sorting

#endif // FORFUN_SORTING_BUBBLE_SORT_HPP_
