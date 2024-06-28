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
#include <concepts>
#include <iterator>

namespace forfun::first_missing_positive {

namespace detail {

template <std::contiguous_iterator Itr>
    requires std::sortable<Itr> and std::integral<std::iter_value_t<Itr>>
constexpr auto quasi_sort(Itr const first, Itr const src) noexcept -> void
{
    using ValType = std::iter_value_t<Itr>;

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

} // namespace detail

namespace base {

template <std::contiguous_iterator Itr, std::sized_sentinel_for<Itr> Sentinel>
    requires std::sortable<Itr> and std::integral<std::iter_value_t<Itr>>
[[nodiscard]] constexpr auto lowest_missing(
    Itr const begin, Sentinel const end) noexcept -> std::iter_value_t<Itr>
{
    using ValType = std::iter_value_t<Itr>;

    auto max{end - begin};

    for (auto itr{begin}; itr != end; ++itr)
    {
        if (auto const current{*itr}; current < ValType{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *itr = ValType{0};
        }
        else
        {
            detail::quasi_sort(begin, itr);
        }
    }

    ValType min_num{1};

    auto const endItr{begin + max};
    for (auto itr{begin}; itr != endItr; ++itr)
    {
        if (*itr == min_num)
        {
            ++min_num;
        }
    }

    return min_num;
}

} // namespace base

namespace fast {

template <std::contiguous_iterator Itr, std::sized_sentinel_for<Itr> Sentinel>
    requires std::sortable<Itr> and std::integral<std::iter_value_t<Itr>>
[[nodiscard]] constexpr auto lowest_missing(
    Itr const begin, Sentinel const end) noexcept -> std::iter_value_t<Itr>
{
    using ValType = std::iter_value_t<Itr>;

    auto max{end - begin};

    for (auto itr{begin}; itr != end; ++itr)
    {
        if (auto const current{*itr}; current < ValType{1})
        {
            --max;
        }
        else if (current > max)
        {
            --max;
            *itr = ValType{0};
        }
        else
        {
            detail::quasi_sort(begin, itr);
        }
    }

    ValType min_num{1};

    for (std::iter_difference_t<Itr> i{0}; i < max; ++i)
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
