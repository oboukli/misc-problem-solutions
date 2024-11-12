// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/meeting_rooms.hpp"

#include <ostream>

namespace forfun::meeting_rooms {

auto operator<<(std::ostream& os, interval const intrvl) -> std::ostream&
{
    return os << '{' << intrvl.start << ", " << intrvl.end << '}';
}

} // namespace forfun::meeting_rooms
