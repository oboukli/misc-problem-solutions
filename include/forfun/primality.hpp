// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

// https://en.wikipedia.org/wiki/Primality_test

#ifndef FORFUN_PRIMALITY_HPP_
#define FORFUN_PRIMALITY_HPP_

#include <cmath>
#include <concepts>
#include <utility>

namespace forfun::primality {

template <std::unsigned_integral UInteger>
/*constexpr*/ inline auto
is_prime(UInteger const n) noexcept(noexcept(std::sqrt(std::declval<UInteger>())
)) -> bool
{
    if (n < UInteger{2U})
    {
        return false;
    }

    if (n == UInteger{2U})
    {
        return true;
    }

    if ((n & UInteger{1U}) == UInteger{0U})
    {
        return false;
    }

    UInteger const r{static_cast<UInteger>(std::sqrt(n))};
    for (UInteger i{3U}; i <= r; ++i)
    {
        if (((i & UInteger{1U}) != UInteger{0U}) && ((n % i) == UInteger{0}))
        {
            return false;
        }
    }

    return true;
}

} // namespace forfun::primality

#endif // FORFUN_PRIMALITY_HPP_
