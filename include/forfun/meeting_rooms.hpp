// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// - https://neetcode.io/problems/meeting-schedule
/// - https://neetcode.io/problems/meeting-schedule-ii

#ifndef FORFUN_MEETING_ROOMS_HPP_
#define FORFUN_MEETING_ROOMS_HPP_

#include <concepts>
#include <cstddef>
#include <iterator>
#include <ostream>

namespace forfun::meeting_rooms {

struct interval final {
    int start;

    int end;
};

auto operator<<(std::ostream& os, interval intrvl) -> std::ostream&;

[[nodiscard]] auto constexpr is_conflicting(
    interval const a, interval const b
) noexcept -> bool
{
    return a.end > b.start;
}

/// @note Iterator arguments must be of a container of `interval` elements,
/// where the elements are sorted by the `start` field in non-descending order;
/// Otherwise the behavior of the strategy is undefined.
template <std::forward_iterator Iter>
    requires std::same_as<std::iter_value_t<Iter>, interval>
[[nodiscard]] auto constexpr can_attend(
    Iter iter, std::sentinel_for<Iter> auto const last
) noexcept -> bool
{
    if (iter != last) [[likely]]
    {
        while (std::next(iter) != last)
        {
            if (is_conflicting(*iter, *std::next(iter)))
            {
                return false;
            }

            ++iter;
        }
    }

    return true;
}

/// @note Iterator arguments must be of a container of `interval` elements,
/// where the elements are sorted by the `start` field in non-descending order;
/// Otherwise the behavior of the strategy is undefined.
template <std::input_or_output_iterator Iter>
    requires std::same_as<std::iter_value_t<Iter>, interval>
[[nodiscard]] auto constexpr min_chronotopes(
    Iter iter, std::sentinel_for<Iter> auto const last
) noexcept -> std::size_t
{
    std::size_t chronotopes{1UZ};

    while (std::next(iter) != last) [[likely]]
    {
        if (is_conflicting(*iter, *std::next(iter)))
        {
            ++chronotopes;
        }

        ++iter;
    }

    return chronotopes;
}

} // namespace forfun::meeting_rooms

#endif // FORFUN_MEETING_ROOMS_HPP_
