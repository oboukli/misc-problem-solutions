// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://neetcode.io/problems/meeting-schedule

#ifndef FORFUN_MEETING_ROOMS_HPP_
#define FORFUN_MEETING_ROOMS_HPP_

#include <concepts>
#include <iterator>
#include <ostream>

namespace forfun::meeting_rooms {

struct interval final {
    int start;

    int end;
};

auto operator<<(std::ostream& os, interval intrvl) -> std::ostream&;

/// Assumes input is sorted, by the `start` field of `internal`, in
/// non-descending order, otherwise the behavior of the strategy is undefined.
template <std::input_or_output_iterator Iter>
    requires std::same_as<std::iter_value_t<Iter>, interval>
[[nodiscard]] auto constexpr can_attend(
    Iter first, std::sentinel_for<Iter> auto const last
) noexcept -> bool
{
    if (first != last) [[likely]]
    {
        while (std::next(first) != last)
        {
            if (first->end > std::next(first)->start)
            {
                return false;
            }

            ++first;
        }
    }

    return true;
}

} // namespace forfun::meeting_rooms

#endif // FORFUN_MEETING_ROOMS_HPP_
