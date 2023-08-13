// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Quicksort

#ifndef FORFUN_SORTING_QUICKSORT_HPP_
#define FORFUN_SORTING_QUICKSORT_HPP_

#include <algorithm>
#include <iterator>

namespace forfun::sorting {

namespace {

template <typename T, typename RandomIt>
[[nodiscard]] constexpr inline RandomIt
partition(T& container, RandomIt const lo, RandomIt const hi) noexcept {
    auto const pivot = *hi;

    auto i{std::prev(lo)};
    for (auto j{lo}; j < hi; ++j) {
        if (*j < pivot) {
            ++i;
            std::iter_swap(i, j);
        }
    }

    std::advance(i, 1);
    std::iter_swap(hi, i);

    return i;
}

} // namespace

template <typename T, typename RandomIt>
constexpr inline void
quicksort(T& container, RandomIt const lo, RandomIt const hi) noexcept {
    if (hi > lo) {
        auto const p{partition(container, lo, hi)};

        quicksort(container, lo, std::prev(p));
        quicksort(container, std::next(p), hi);
    }
}
} // namespace forfun::sorting

#endif // FORFUN_SORTING_QUICKSORT_HPP_