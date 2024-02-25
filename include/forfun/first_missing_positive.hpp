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
#include <iterator>

namespace forfun::first_missing_positive {

namespace {

template <std::random_access_iterator RandomIt>
    requires std::integral<std::iter_value_t<RandomIt>>
constexpr inline void
quasi_sort(RandomIt const first, RandomIt const src) noexcept
{
    using ValType = std::iter_value_t<RandomIt>;

    if (auto const n{*src}; n > ValType{0})
    {
        auto const dest{first + std::max<ValType>(ValType{0}, n - ValType{1})};
        if (auto const tmp{*dest}; tmp != n)
        {
            *dest = n;
            *src = tmp;

            quasi_sort(first, src);
        }
    }
}

} // namespace

namespace base {

template <std::random_access_iterator RandomIt>
    requires std::integral<std::iter_value_t<RandomIt>>
[[nodiscard]] constexpr inline std::iter_value_t<RandomIt>
lowest_missing(RandomIt const begin, RandomIt const end) noexcept
{
    using ValType = std::iter_value_t<RandomIt>;

    auto max{end - begin};

    for (auto it{begin}; it != end; ++it)
    {
        if (auto const current{*it}; current < ValType{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *it = ValType{0};
        }
        else
        {
            quasi_sort(begin, it);
        }
    }

    ValType min_num{1};

    auto const endIt{begin + max};
    for (auto it{begin}; it != endIt; ++it)
    {
        if (*it == min_num)
        {
            ++min_num;
        }
    }

    return min_num;
}

} // namespace base

namespace fast {

template <std::random_access_iterator RandomIt>
    requires std::integral<std::iter_value_t<RandomIt>>
[[nodiscard]] constexpr inline std::iter_value_t<RandomIt>
lowest_missing(RandomIt const begin, RandomIt const end) noexcept
{
    using ValType = std::iter_value_t<RandomIt>;

    auto max{end - begin};

    for (auto it{begin}; it != end; ++it)
    {
        if (auto const current{*it}; current < ValType{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *it = ValType{0};
        }
        else
        {
            quasi_sort(begin, it);
        }
    }

    ValType min_num{1};

    for (std::iter_difference_t<RandomIt> i{0}; i < max; ++i)
    {
        if (begin[i] == min_num)
        {
            ++min_num;
        }
    }

    return min_num;
}

} // namespace fast

} // namespace forfun::first_missing_positive

#endif // FORFUN_FIRST_MISSING_POSITIVE_HPP_
