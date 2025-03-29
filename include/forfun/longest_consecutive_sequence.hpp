// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/longest-consecutive-sequence/

#ifndef FORFUN_LONGEST_CONSECUTIVE_SEQUENCE_HPP_
#define FORFUN_LONGEST_CONSECUTIVE_SEQUENCE_HPP_

#include <algorithm>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <set>
#include <type_traits>

namespace forfun::longest_consecutive_sequence {

namespace counted {

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto longest_consecutive(Iter iter, Sentinel const last) noexcept
    -> std::size_t
{
    if (iter == last) [[unlikely]]
    {
        return std::size_t{0U};
    }

    std::sort(iter, last);
    auto const last_unique{std::unique(iter, last)};

    std::size_t top_streak{1U};
    std::size_t streak{1U};

    for (auto iter_b{std::next(iter)}; iter_b != last_unique; ++iter, ++iter_b)
    {
        if (((*iter) + std::iter_value_t<Iter>{1}) == *iter_b)
        {
            ++streak;
            top_streak = std::max(streak, top_streak);
        }
        else
        {
            streak = std::size_t{1U};

            // Conclude if no higher streak is possible.
            if (static_cast<std::size_t>(std::distance(iter_b, last_unique))
                <= top_streak)
            {
                break;
            }
        }
    }

    return top_streak;
}

} // namespace counted

namespace measured {

namespace detail {

template <std::input_iterator Iter>
[[nodiscard]] constexpr auto recalc_top_streak(
    Iter const first,
    std::sized_sentinel_for<Iter> auto const last,
    std::size_t const top_streak
) noexcept -> std::size_t
{
    return std::max(
        static_cast<std::size_t>(std::distance(first, last)), top_streak
    );
}

} // namespace detail

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto longest_consecutive(Iter iter, Sentinel const last) noexcept
    -> std::size_t
{
    if (iter == last) [[unlikely]]
    {
        return std::size_t{0U};
    }

    std::sort(iter, last);
    auto const last_unique{std::unique(iter, last)};

    std::size_t top_streak{1U};
    auto streak_begin_iter{iter};

    auto iter_b{std::next(iter)};
    for (; iter_b != last_unique; ++iter, ++iter_b)
    {
        if (((*iter) + std::iter_value_t<Iter>{1}) != *iter_b)
        {
            top_streak = detail::recalc_top_streak(
                streak_begin_iter, iter_b, top_streak
            );

            // Conclude if no higher streak is possible.
            if (top_streak
                >= static_cast<std::size_t>(std::distance(iter_b, last_unique)))
            {
                return top_streak;
            }

            streak_begin_iter = iter_b;
        }
    }

    return detail::recalc_top_streak(streak_begin_iter, iter_b, top_streak);
}

} // namespace measured

namespace set_sliding {

template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
longest_consecutive(Iter const first, Sentinel const last) noexcept
    -> std::size_t
{
    if (first == last) [[unlikely]]
    {
        return std::size_t{0U};
    }

    using ValueType = std::iter_value_t<Iter>;

    std::set<ValueType> const lookup_set(first, last);

    std::size_t top_streak{1U};
    std::size_t streak{1U};

    for (auto iter_a{lookup_set.cbegin()},
         iter_b{std::next(lookup_set.cbegin())};
         iter_b != lookup_set.cend();
         ++iter_a, ++iter_b)
    {
        if (ValueType{(*iter_a) + 1} == *iter_b)
        {
            ++streak;
            top_streak = std::max(streak, top_streak);
        }
        else
        {
            streak = std::size_t{1U};

            // Conclude if no higher streak is possible.
            if (static_cast<std::size_t>(
                    std::distance(iter_b, lookup_set.cend())
                )
                <= top_streak)
            {
                break;
            }
        }
    }

    return top_streak;
}

} // namespace set_sliding

namespace set_scanning {

template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::integral<std::iter_value_t<Iter>>
[[nodiscard]] auto
longest_consecutive(Iter const first, Sentinel const last) noexcept
    -> std::size_t
{
    using ValueType = std::iter_value_t<Iter>;

    std::set<ValueType> const lookup(first, last);
    static_assert(
        std::is_same_v<std::size_t, typename decltype(lookup)::size_type>
    );

    std::size_t top_streak{0U};

    auto lu_iter{lookup.cbegin()};
    for (std::size_t i{0U}; i < lookup.size(); ++i)
    {
        auto const a{*lu_iter};
        if (not lookup.contains(a - 1))
        {
            ValueType b{a + 1};
            while (lookup.contains(b))
            {
                ++b;
            }

            top_streak = std::max(static_cast<std::size_t>(b - a), top_streak);

            if (lookup.size() - i <= top_streak)
            {
                break;
            }
        }

        ++lu_iter;
    }

    return top_streak;
}

} // namespace set_scanning

} // namespace forfun::longest_consecutive_sequence

#endif // FORFUN_LONGEST_CONSECUTIVE_SEQUENCE_HPP_
