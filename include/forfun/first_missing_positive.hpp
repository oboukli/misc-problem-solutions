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
#include <type_traits>

namespace forfun::first_missing_positive {

namespace {

template <typename Container>
    requires std::integral<std::decay_t<typename Container::value_type>>
constexpr inline void quasi_sort(
    typename Container::iterator const first,
    typename Container::iterator const src) noexcept
{
    using ValTyp = std::decay_t<typename Container::value_type>;

    if (auto const n{*src}; n > ValTyp{0})
    {
        auto const dest{std::next(
            first,
            static_cast<Container::difference_type>(
                std::max<ValTyp>(ValTyp{0}, n - ValTyp{1})))};
        if (auto const tmp{*dest}; tmp != n)
        {
            *dest = n;
            *src = tmp;

            quasi_sort<Container>(first, src);
        }
    }
}

} // namespace

template <typename Container>
    requires std::integral<std::decay_t<typename Container::value_type>>
[[nodiscard]] constexpr inline Container::value_type
lowest_missing(Container& numbers) noexcept
{
    using ValTyp = std::decay_t<typename Container::value_type>;

    auto const begin{numbers.begin()};

    auto max{numbers.size()};

    {
        auto const end{numbers.end()};
        for (auto it{begin}; it != end; ++it)
        {
            if (auto const current{*it}; current < ValTyp{1})
            {
                --max;
            }
            else if (static_cast<std::size_t>(current) > max)
            {
                --max;
                *it = ValTyp{0};
            }
            else
            {
                quasi_sort<Container>(begin, it);
            }
        }
    }

    ValTyp min_num{1};

    {
        auto const endIt{
            std::next(begin, static_cast<Container::difference_type>(max))};
        for (auto it{begin}; it != endIt; ++it)
        {
            if (*it == min_num)
            {
                ++min_num;
            }
        }
    }

    return min_num;
}

} // namespace forfun::first_missing_positive

#endif // FORFUN_FIRST_MISSING_POSITIVE_HPP_
