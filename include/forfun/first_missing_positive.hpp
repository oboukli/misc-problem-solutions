// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// - https://simontoth.substack.com/p/daily-bite-of-c-smallest-missing
/// - https://compiler-explorer.com/z/G7r4rebhd
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
#include <concepts>
#include <iterator>

namespace forfun::first_missing_positive {

namespace detail {

template <std::contiguous_iterator Iter>
    requires std::sortable<Iter> and std::integral<std::iter_value_t<Iter>>
constexpr auto quasi_sort(Iter const first, Iter const src) noexcept -> void
{
    using ValType = std::iter_value_t<Iter>;

    if (auto const n{*src}; n > ValType{})
    {
        auto const dest{first + std::max<ValType>(ValType{}, n - ValType{1})};
        if (auto const aux{*dest}; aux != n)
        {
            *dest = n;
            *src = aux;

            quasi_sort(first, src);
        }
    }
}

} // namespace detail

namespace base {

template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::sortable<Iter> and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
lowest_missing(Iter const first, Sentinel const last) noexcept
    -> std::iter_value_t<Iter>
{
    using ValType = std::iter_value_t<Iter>;

    auto max{last - first};

    for (auto iter{first}; iter != last; ++iter)
    {
        if (auto const current{*iter}; current < ValType{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *iter = ValType{};
        }
        else
        {
            detail::quasi_sort(first, iter);
        }
    }

    ValType min_num{1};

    auto const endIter{first + max};
    for (auto iter{first}; iter != endIter; ++iter)
    {
        if (*iter == min_num)
        {
            ++min_num;
        }
    }

    return min_num;
}

} // namespace base

namespace fast {

template <std::contiguous_iterator Iter, std::sized_sentinel_for<Iter> Sentinel>
    requires std::sortable<Iter> and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
lowest_missing(Iter const first, Sentinel const last) noexcept
    -> std::iter_value_t<Iter>
{
    using ValType = std::iter_value_t<Iter>;

    auto max{last - first};

    for (auto iter{first}; iter != last; ++iter)
    {
        if (auto const current{*iter}; current < ValType{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *iter = ValType{};
        }
        else
        {
            detail::quasi_sort(first, iter);
        }
    }

    ValType min_num{1};

    for (std::iter_difference_t<Iter> i{}; i < max; ++i)
    {
        if (first[i] == min_num)
        {
            ++min_num;
        }
    }

    return min_num;
}

} // namespace fast

} // namespace forfun::first_missing_positive

#endif // FORFUN_FIRST_MISSING_POSITIVE_HPP_
