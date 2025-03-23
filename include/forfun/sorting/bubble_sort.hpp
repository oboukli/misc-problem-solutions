// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Bubble_sort

#ifndef FORFUN_SORTING_BUBBLE_SORT_HPP_
#define FORFUN_SORTING_BUBBLE_SORT_HPP_

#include <algorithm>
#include <iterator>

namespace forfun::sorting {

namespace plain {

template <std::sortable Iter, std::sentinel_for<Iter> Sentinel>
    requires std::bidirectional_iterator<Sentinel>
constexpr auto bubble_sort(Iter const first, Sentinel last) noexcept -> void
{
    if (first == last) [[unlikely]]
    {
        return;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    bool f /*[[indeterminate]]*/;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        --last;
        f = false;
        for (Iter it_i{first}; it_i != last; ++it_i)
        {
            auto const it_ii{std::next(it_i)};
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

template <std::sortable Iter, std::sentinel_for<Iter> Sentinel>
    requires std::bidirectional_iterator<Sentinel>
constexpr auto bubble_sort(Iter const first, Sentinel last) noexcept -> void
{
    if (first == last) [[unlikely]]
    {
        return;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
    bool f /*[[indeterminate]]*/;
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-do-while)
    do
    {
        --last;
        f = false;
        for (Iter it_i{first}; it_i != last; ++it_i)
        {
            if (*it_i > *std::next(it_i))
            {
                std::iter_swap(it_i, std::next(it_i));
                f = true;
            }
        }
    } while (f);
}

} // namespace stl

} // namespace forfun::sorting

#endif // FORFUN_SORTING_BUBBLE_SORT_HPP_
