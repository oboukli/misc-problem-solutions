// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Bubble_sort

#ifndef FORFUN_SORTING_BUBBLE_SORT_HPP_
#define FORFUN_SORTING_BUBBLE_SORT_HPP_

#include <algorithm>

namespace forfun::sorting {

namespace plain {

template <typename RandomIt>
constexpr inline void bubble_sort(RandomIt const begin, RandomIt end) noexcept
{
    bool f;
    do
    {
        f = false;
        for (RandomIt i{begin}; i != end; ++i)
        {
            auto const ii{i + 1};
            if (*i > *ii)
            {
                auto const tmp{*ii};
                *ii = *i;
                *i = tmp;

                f = true;
            }
        }
        --end;
    } while (f);
}

} // namespace plain

namespace stl {

template <typename RandomIt>
constexpr inline void bubble_sort(RandomIt const begin, RandomIt end) noexcept
{
    bool f;
    do
    {
        f = false;
        for (RandomIt i{begin}; i != end; ++i)
        {
            if (*i > *(i + 1))
            {
                std::iter_swap(i, i + 1);
                f = true;
            }
        }
        --end;
    } while (f);
}

} // namespace stl

} // namespace forfun::sorting

#endif // FORFUN_SORTING_BUBBLE_SORT_HPP_
