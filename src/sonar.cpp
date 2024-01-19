// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/sonar.hpp"

#include <algorithm>
#include <cstdlib>

namespace forfun::sonar {

int count_ships(Sonar const& sonar, Area const area)
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

    return count_ships(
               sonar,
               {
                   area.top,
                   mh0,
                   area.left,
                   mw0,
               })
        + count_ships(
               sonar,
               {
                   area.top,
                   mh0,
                   mw1,
                   area.right,
               })
        + count_ships(
               sonar,
               {
                   mh1,
                   area.bottom,
                   area.left,
                   mw0,
               })
        + count_ships(
               sonar,
               {
                   mh1,
                   area.bottom,
                   mw1,
                   area.right,
               });
}

bool Sonar::ping(Area area) const
{
    return std::ranges::any_of(coords, [&area](Coord const& coord) {
        return coord.x >= area.top && coord.x <= area.bottom
            && coord.y >= area.left && coord.y <= area.right;
    });
}

} // namespace forfun::sonar
