// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Greatest_common_divisor

#ifndef FORFUN_GCD_HPP_
#define FORFUN_GCD_HPP_

#include <cstdlib>

namespace forfun::gcd::euclid::recursive {

namespace detail {

[[nodiscard]] constexpr auto gcd_imp(int const m, int const n) noexcept -> int
{
    if (n == 0)
    {
        return m;
    }

    return gcd_imp(n, m % n);
}

} // namespace detail

[[nodiscard]] /*constexpr*/ inline auto gcd(int const m, int const n) noexcept
    -> int
{
    return std::abs(detail::gcd_imp(m, n));
}

} // namespace forfun::gcd::euclid::recursive

#endif // FORFUN_GCD_HPP_
