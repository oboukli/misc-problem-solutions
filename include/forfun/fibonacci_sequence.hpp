// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Fibonacci_sequence

#ifndef FORFUN_FIBONACCI_SEQUENCE_HPP_
#define FORFUN_FIBONACCI_SEQUENCE_HPP_

#include <concepts>

namespace forfun::fibonacci::sequence {

namespace slow {

template <std::integral T, typename State, std::invocable<T, State&> Func>
auto fib_seq(T const max, Func func, State& state) noexcept(noexcept(func))
    -> void
{
    for (T i{0}, j{1}; i <= max;)
    {
        func(i, state);

        T const aux{j + i};
        i = j;
        j = aux;
    }
}

} // namespace slow

namespace fast {

template <std::integral T, typename State, std::invocable<T, State&> Func>
auto fib_seq(T const max, Func func, State& state) noexcept(noexcept(func))
    -> void
{
    for (T i{0}, j{1}; i <= max;)
    {
        func(i, state);

        j += i;
        i = j - i;
    }
}

} // namespace fast

namespace creel {

template <std::integral T, typename State, std::invocable<T, State&> Func>
auto fib_seq(T const max, Func func, State& state) noexcept(noexcept(func))
    -> void
{
    // Adapted from: https://youtu.be/IZc4Odd3K2Q?t=949
    for (T i{0}, j{1}; i <= max;)
    {
        func(i, state);

        j = (i += j) - j;
    }
}

} // namespace creel

} // namespace forfun::fibonacci::sequence

#endif // FORFUN_FIBONACCI_SEQUENCE_HPP_
