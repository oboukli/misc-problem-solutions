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

template <typename Iter>
    requires std::contiguous_iterator<Iter>
    and std::sortable<Iter>
    and std::integral<std::iter_value_t<Iter>>
constexpr auto quasi_sort(Iter const first, Iter const src) noexcept -> void
{
    using std::max;

    using ValType = std::iter_value_t<Iter>;

    if (auto const num{*src}; num > ValType{})
    {
        auto const dest{first + max<ValType>(ValType{}, num - ValType{1})};
        if (auto const aux{*dest}; aux != num)
        {
            *dest = num;
            *src = aux;

            quasi_sort(first, src);
        }
    }
}

} // namespace detail

namespace base {

template <typename Iter, typename Sentinel>
    requires std::contiguous_iterator<Iter>
    and std::sized_sentinel_for<Iter, Sentinel>
    and std::sortable<Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
lowest_missing(Iter const first, Sentinel const last) noexcept
    -> std::iter_value_t<Iter>
{
    using std::distance;
    using std::next;

    using ValType = std::iter_value_t<Iter>;

    auto max{distance(first, last)};

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

    auto const end_iter{next(first, max)};
    for (auto iter{first}; iter != end_iter; ++iter)
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

template <typename Iter, typename Sentinel>
    requires std::contiguous_iterator<Iter>
    and std::sized_sentinel_for<Iter, Sentinel>
    and std::sortable<Iter>
    and std::integral<std::iter_value_t<Iter>>
[[nodiscard]] constexpr auto
lowest_missing(Iter const first, Sentinel const last) noexcept
    -> std::iter_value_t<Iter>
{
    using std::distance;
    using std::next;

    using ValType = std::iter_value_t<Iter>;

    auto max{distance(first, last)};

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
        if (*next(first, i) == min_num)
        {
            ++min_num;
        }
    }

    return min_num;
}

} // namespace fast

} // namespace forfun::first_missing_positive

#endif // FORFUN_FIRST_MISSING_POSITIVE_HPP_
