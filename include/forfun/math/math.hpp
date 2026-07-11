// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_MATH_HPP_
#define FORFUN_COMMON_MATH_HPP_

#include <cassert>
#include <cstddef>
#include <utility>

namespace forfun::math {

namespace alternative {

/// @note This functions offers no performance improvement over utilizing
/// floating-point division along with \c std::ceil. For more information, refer
/// to the developer notes.
///
/// @note Both of @p a and @p b must be non-zero and positive.
[[nodiscard]] constexpr auto div_ceil(int const a, int const b) noexcept -> int
{
    assert(a != 0);
    assert(b != 0);

    // Source: https://stackoverflow.com/a/2745086
    return 1 + ((a - 1) / b);
}

} // namespace alternative

namespace core {

[[nodiscard]] /*constexpr*/ auto div_ceil(int a, int b) noexcept -> int;

} // namespace core

namespace lookup {

/// Compact lookup table for Catalan numbers by index \p n
/// @pre The index @p n must be greater or equal to one, and less than or equal
/// to eight.
template <typename ReturnType = std::size_t>
[[nodiscard]] constexpr auto catalan(int const n) -> ReturnType
{
    assert((n >= 1) && (n <= 8));

    // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
    switch (n)
    {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 5;
    case 4:
        return 14;
    case 5:
        return 42;
    case 6:
        return 132;
    case 7:
        return 429;
    case 8:
        return 1'430;
    default:
        break;
    }
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

    std::unreachable();
}

} // namespace lookup

} // namespace forfun::math

#endif // FORFUN_COMMON_MATH_HPP_
