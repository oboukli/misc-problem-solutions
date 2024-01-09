// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Insertion_sort

#ifndef FORFUN_SORTING_INSERTION_HPP_
#define FORFUN_SORTING_INSERTION_HPP_

#include <algorithm>

namespace forfun::sorting {

template <typename RandomIt>
constexpr inline void
insertion_sort(RandomIt const begin, RandomIt const end) noexcept
{
    if (begin != end)
    {
        for (RandomIt i{begin + 1}; i != end; ++i)
        {
            for (RandomIt j{i}; j != begin && (*j < *(j - 1)); --j)
            {
                std::iter_swap(j, j - 1);
            }
        }
    }
}

} // namespace forfun::sorting

#endif // FORFUN_SORTING_INSERTION_HPP_
