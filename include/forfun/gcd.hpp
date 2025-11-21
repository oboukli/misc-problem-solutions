// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Greatest_common_divisor

#ifndef FORFUN_GCD_HPP_
#define FORFUN_GCD_HPP_

#include <algorithm>
#include <cstdlib>

namespace forfun::gcd::euclid {

namespace iterative {

[[nodiscard]] constexpr auto gcd_p(int a, int b) noexcept -> int
{
    while (b != 0)
    {
        auto const aux{b};
        b = a % b;
        a = aux;
    }

    return a;
}

[[nodiscard]] /*constexpr*/ inline auto gcd(int a, int b) noexcept -> int
{
    return std::abs(gcd_p(a, b));
}

} // namespace iterative

namespace recursive {

[[nodiscard]] constexpr auto gcd_p(int const a, int const b) noexcept -> int
{
    if (b == 0) [[unlikely]]
    {
        return a;
    }

    return gcd_p(b, a % b);
}

[[nodiscard]] /*constexpr*/ inline auto gcd(int const a, int const b) noexcept
    -> int
{
    return std::abs(gcd_p(a, b));
}

} // namespace recursive

namespace subtraction_based {

[[nodiscard]] constexpr auto gcd_p(int a, int b) noexcept -> int
{
    if (auto const& [min, max]{std::minmax(a, b)}; min == 0)
    {
        return max;
    }

    while (a != b)
    {
        if (a > b)
        {
            a -= b;
        }
        else
        {
            b -= a;
        }
    }

    return a;
}

[[nodiscard]] /*constexpr*/ inline auto gcd(int a, int b) noexcept -> int
{
    return gcd_p(std::abs(a), std::abs(b));
}

} // namespace subtraction_based

} // namespace forfun::gcd::euclid

#endif // FORFUN_GCD_HPP_
