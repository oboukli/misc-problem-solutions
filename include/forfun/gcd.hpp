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

namespace {

[[nodiscard]] constexpr inline int gcd_(int const m, int const n) noexcept
{
    if (n == 0)
    {
        return m;
    }

    return gcd_(n, m % n);
}

} // namespace

[[nodiscard]] /*constexpr*/ inline int gcd(int const m, int const n) noexcept
{
    return std::abs(gcd_(m, n));
}

} // namespace forfun::gcd::euclid::recursive

#endif // FORFUN_GCD_HPP_
