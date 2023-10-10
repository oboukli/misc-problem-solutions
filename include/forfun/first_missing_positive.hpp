// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://simontoth.substack.com/p/daily-bite-of-c-smallest-missing
/// https://compiler-explorer.com/z/G7r4rebhd
///
/// Given a list of integers, determine the smallest missing
/// positive integer.
///
/// Importantly your solution must run in O(n) time, and while
/// you are permitted to modify the input, you can only use
/// constant additional memory.

#ifndef FORFUN_FIRST_MISSING_POSITIVE_HPP_
#define FORFUN_FIRST_MISSING_POSITIVE_HPP_

#include <algorithm>
#include <cstddef>
#include <iterator>

namespace forfun::first_missing_positive {

namespace {

template <typename RandomIt>
constexpr inline void quasi_sort(RandomIt first, RandomIt const src) noexcept
{
    auto const n{*src};

    if (n > 0)
    {
        RandomIt const dest{std::next(first, std::max(0, n - 1))};
        if (auto const tmp{*dest}; tmp != n)
        {
            *dest = n;
            *src = tmp;

            quasi_sort(first, src);
        }
    }
}

} // namespace

template <typename T>
[[nodiscard]] constexpr inline int lowest_missing(T& numbers) noexcept
{
    auto begin{numbers.begin()};
    auto end{numbers.end()};
    auto max{numbers.size()};

    for (auto it{begin}; it != end; ++it)
    {
        int const current{*it};
        if (current < 1)
        {
            --max;
        }
        else if (static_cast<std::size_t>(current) > max)
        {
            --max;
            *it = 0;
        }
        else
        {
            quasi_sort(begin, it);
        }
    }

    int min_num{1};
    auto const endIt{std::next(begin, static_cast<T::difference_type>(max))};
    for (auto it{begin}; it != endIt; ++it)
    {
        if (*it == min_num)
        {
            ++min_num;
        }
    }

    return min_num;
}

} // namespace forfun::first_missing_positive

#endif // FORFUN_FIRST_MISSING_POSITIVE_HPP_
