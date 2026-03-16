// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/common/math.hpp"

#include <cassert>
#include <cmath>

namespace forfun::common::math::core {

[[nodiscard]] auto div_ceil(int const a, int const b) noexcept -> int
{
    using std::ceil;

    assert(b != 0);

    // We target compilers that are able to optimize this. See developer
    // notes.
    return static_cast<int>(
        ceil(static_cast<double>(a) / static_cast<double>(b))
    );
}

} // namespace forfun::common::math::core
