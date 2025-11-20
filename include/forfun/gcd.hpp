// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Greatest_common_divisor

#ifndef FORFUN_GCD_HPP_
#define FORFUN_GCD_HPP_

#include <cstdlib>

namespace forfun::gcd::euclid::recursive {

namespace detail {

[[nodiscard]] constexpr auto gcd_imp(int const a, int const b) noexcept -> int
{
    if (b == 0) [[unlikely]]
    {
        return a;
    }

    return gcd_imp(b, a % b);
}

} // namespace detail

[[nodiscard]] /*constexpr*/ inline auto gcd(int const a, int const b) noexcept
    -> int
{
    return std::abs(detail::gcd_imp(a, b));
}

} // namespace forfun::gcd::euclid::recursive

#endif // FORFUN_GCD_HPP_
