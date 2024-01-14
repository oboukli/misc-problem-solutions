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

template <typename Iter>
    requires std::contiguous_iterator<Iter>
constexpr inline void bubble_sort(Iter const begin, Iter end) noexcept
{
    using Diff = std::iterator_traits<Iter>::difference_type;

    if (begin == end)
    {
        return;
    }

    bool f;
    do
    {
        --end;
        f = false;
        for (Iter i{begin}; i != end; ++i)
        {
            auto const ii{i + Diff{1}};
            if (*i > *ii)
            {
                auto const tmp{*ii};
                *ii = *i;
                *i = tmp;

                f = true;
            }
        }
    } while (f);
}

} // namespace plain

namespace stl {

template <typename Iter>
    requires std::contiguous_iterator<Iter>
constexpr inline void bubble_sort(Iter const begin, Iter end) noexcept
{
    using Diff = std::iterator_traits<Iter>::difference_type;

    if (begin == end)
    {
        return;
    }

    bool f;
    do
    {
        --end;
        f = false;
        for (Iter i{begin}; i != end; ++i)
        {
            if (*i > *(i + Diff{1}))
            {
                std::iter_swap(i, i + Diff{1});
                f = true;
            }
        }
    } while (f);
}

} // namespace stl

} // namespace forfun::sorting

#endif // FORFUN_SORTING_BUBBLE_SORT_HPP_
