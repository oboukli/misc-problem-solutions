// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Fibonacci_sequence

#ifndef FORFUN_FIBONACCI_SEQUENCE_HPP_
#define FORFUN_FIBONACCI_SEQUENCE_HPP_

#include <concepts>
#include <utility>

namespace forfun::fibonacci::sequence {

// clang-format off
template <typename Func, typename... Args>
concept noexcept_callable
    = std::invocable<Func, Args...>
    and requires(Func&& func, Args&&... args) {
        requires noexcept(func(std::forward<Args>(args)...));
    };
// clang-format on

namespace slow {

template <std::integral T, typename State, noexcept_callable<T, State&> Func>
void fib_seq(T const max, Func func, State& state) noexcept
{
    for (T i{0}, j{1}; i <= max;)
    {
        func(i, state);

        T const tmp = j + i;
        i = j;
        j = tmp;
    }
}

} // namespace slow

namespace fast {

template <std::integral T, typename State, noexcept_callable<T, State&> Func>
void fib_seq(T const max, Func func, State& state) noexcept
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

template <std::integral T, typename State, noexcept_callable<T, State&> Func>
void fib_seq(T const max, Func func, State& state) noexcept
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
