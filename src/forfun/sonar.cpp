// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/sonar.hpp"

#include <algorithm>
#include <cstdlib>

namespace forfun::sonar {

[[nodiscard]] auto
count_ships(Sonar const& sonar, Area const area) noexcept -> int
{
    if (!sonar.ping(area))
    {
        return 0;
    }

    int const width{std::abs(area.right - area.left)};
    int const height{std::abs(area.bottom - area.top)};

    if ((width + height) == 0)
    {
        return 1;
    }

    int const mw0{area.left + (width / 2)};
    int const mw1{mw0 + 1};
    int const mh0{area.top + (height / 2)};
    int const mh1{mh0 + 1};

    // clang-format off
    return (
        count_ships(
            sonar,
            {
                .top = area.top,
                .bottom = mh0,
                .left = area.left,
                .right = mw0,
            }
        ) +
        count_ships(
            sonar,
            {
                .top = area.top,
                .bottom = mh0,
                .left = mw1,
                .right = area.right,
            }
        ) +
        count_ships(
            sonar,
            {
                .top = mh1,
                .bottom = area.bottom,
                .left = area.left,
                .right = mw0,
            }
        ) +
        count_ships(
            sonar,
            {
                .top = mh1,
                .bottom = area.bottom,
                .left = mw1,
                .right = area.right,
            }
        )
    );
    // clang-format on
}

[[nodiscard]] auto Sonar::ping(Area const area) const noexcept -> bool
{
    return std::ranges::any_of(coords_, [&area](Coord const& coord) {
        return coord.x >= area.top
            && coord.x <= area.bottom
            && coord.y >= area.left
            && coord.y <= area.right;
    });
}

} // namespace forfun::sonar
