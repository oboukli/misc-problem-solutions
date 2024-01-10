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

template <typename Iter>
    requires std::contiguous_iterator<Iter>
constexpr inline void insertion_sort(Iter const begin, Iter const end) noexcept
{
    using Diff = std::iterator_traits<Iter>::difference_type;

    if (begin != end)
    {
        for (Iter i{begin + Diff{1}}; i != end; ++i)
        {
            for (Iter j{i}; j != begin && (*j < *(j - Diff{1})); --j)
            {
                std::iter_swap(j, j - Diff{1});
            }
        }
    }
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_INSERTION_HPP_
