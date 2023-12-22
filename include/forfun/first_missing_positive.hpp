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
#include <type_traits>

namespace forfun::first_missing_positive {

namespace {

template <
    typename RandomIt,
    typename ValTyp = std::iterator_traits<RandomIt>::value_type,
    typename Diff = std::iterator_traits<RandomIt>::difference_type>
    requires std::random_access_iterator<RandomIt> && std::integral<ValTyp>
constexpr inline void
quasi_sort(RandomIt const first, RandomIt const src) noexcept
{
    if (auto const n{*src}; n > ValTyp{0})
    {
        auto const dest{first + std::max<ValTyp>(ValTyp{0}, n - ValTyp{1})};
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

template <
    typename RandomIt,
    typename ValTyp = std::iterator_traits<RandomIt>::value_type>
    requires std::random_access_iterator<RandomIt> && std::integral<ValTyp>
[[nodiscard]] constexpr inline ValTyp
lowest_missing(RandomIt const begin, RandomIt const end) noexcept
{
    auto max{end - begin};

    for (auto it{begin}; it != end; ++it)
    {
        if (auto const current{*it}; current < ValTyp{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *it = ValTyp{0};
        }
        else
        {
            quasi_sort(begin, it);
        }
    }

    ValTyp min_num{1};

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

template <
    typename RandomIt,
    typename ValTyp = std::iterator_traits<RandomIt>::value_type,
    typename Diff = std::iterator_traits<RandomIt>::difference_type>
    requires std::random_access_iterator<RandomIt> && std::integral<ValTyp>
[[nodiscard]] constexpr inline ValTyp
lowest_missing(RandomIt const begin, RandomIt const end) noexcept
{
    auto max{end - begin};

    for (auto it{begin}; it != end; ++it)
    {
        if (auto const current{*it}; current < ValTyp{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *it = ValTyp{0};
        }
        else
        {
            quasi_sort(begin, it);
        }
    }

    ValTyp min_num{1};

    for (Diff i{0}; i < max; ++i)
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
