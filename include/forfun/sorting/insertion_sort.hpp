// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Insertion_sort

#ifndef FORFUN_SORTING_INSERTION_HPP_
#define FORFUN_SORTING_INSERTION_HPP_

#include <algorithm>
#include <iterator>

namespace forfun::sorting {

template <std::contiguous_iterator Iter>
constexpr inline void insertion_sort(Iter const begin, Iter const end) noexcept
{
    using DiffType = std::iter_difference_t<Iter>;

    if (begin != end)
    {
        for (Iter i{begin + DiffType{1}}; i != end; ++i)
        {
            for (Iter j{i}; j != begin && (*j < *(j - DiffType{1})); --j)
            {
                std::iter_swap(j, j - DiffType{1});
            }
        }
    }
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_INSERTION_HPP_
