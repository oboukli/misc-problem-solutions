// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_MATH_HPP_
#define FORFUN_COMMON_MATH_HPP_

#include <cassert>

namespace forfun::common::math {

/// @note This functions offers no performance improvement over utilizing
/// floating-point division along with \c std::ceil. For more information, refer
/// to the developer notes.
///
/// @note Both of @p a and @p b must be non-zero and positive.
[[nodiscard]] constexpr auto div_ceil(int const a, int const b) -> int
{
    assert(a != 0);
    assert(b != 0);

    // Source: https://stackoverflow.com/a/2745086
    return 1 + ((a - 1) / b);
}

} // namespace forfun::common::math

#endif // FORFUN_COMMON_MATH_HPP_
