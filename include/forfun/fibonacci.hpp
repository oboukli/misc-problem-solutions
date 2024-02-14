// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Fibonacci_sequence

#ifndef FORFUN_FIBONACCI_HPP_
#define FORFUN_FIBONACCI_HPP_

#include <type_traits>
#include <utility>

namespace forfun::fibonacci {

namespace iterative {

template <typename T>
    requires std::integral<T>
    and std::is_same_v<T, decltype(std::declval<T>() + std::declval<T>())>
[[nodiscard]] constexpr inline T fib(T const n) noexcept
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

template <typename T>
    requires std::integral<T>
    and std::is_same_v<T, decltype(std::declval<T>() + std::declval<T>())>
[[nodiscard]] constexpr inline T fib(T const n) noexcept
{
    if (n <= T{2})
    {
        if (n < T{1})
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
