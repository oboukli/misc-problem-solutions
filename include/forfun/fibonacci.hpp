// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Fibonacci_sequence

#ifndef FORFUN_FIBONACCI_HPP_
#define FORFUN_FIBONACCI_HPP_

#include "forfun/common/concepts.hpp"

namespace forfun::fibonacci {

namespace iterative {

template <common::concepts::addition_unpromoted T>
[[nodiscard]] constexpr auto fib(T const n) noexcept -> T
{
    T a{0};

    for (T i{0}, b{1}; i < n; ++i)
    {
        T const c{a + b};
        a = b;
        b = c;
    }

    return a;
}

} // namespace iterative

namespace recursive {

template <common::concepts::addition_unpromoted T>
[[nodiscard]] constexpr auto fib(T const n) noexcept -> T
{
    if (n <= T{2}) [[unlikely]]
    {
        if (n < T{1}) [[unlikely]]
        {
            return T{0};
        }

        return T{1};
    }

    return fib(n - T{2}) + fib(n - T{1});
}

} // namespace recursive

} // namespace forfun::fibonacci

#endif // FORFUN_FIBONACCI_HPP_
