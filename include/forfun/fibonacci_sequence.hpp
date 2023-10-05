// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Fibonacci_sequence

#ifndef FORFUN_FIBONACCI_SEQUENCE_HPP_
#define FORFUN_FIBONACCI_SEQUENCE_HPP_

#include <concepts>

namespace forfun::fibonacci::sequence {

template <typename T, typename TState>
    requires std::integral<T>
using callback_t = void(*)(T const, TState* const state) noexcept;

namespace slow {

template <typename T, typename TState>
    requires std::integral<T>
void fib_seq(
    T const max, callback_t<T, TState> const cb, TState* const state) noexcept
{
    for (T i{0}, j{1}, tmp{0}; i <= max;)
    {
        cb(i, state);

        tmp = j + i;
        i = j;
        j = tmp;
    }
}

} // namespace slow

namespace fast {

template <typename T, typename TState>
    requires std::integral<T>
void fib_seq(
    T const max, callback_t<T, TState> const cb, TState* const state) noexcept
{
    for (T i{0}, j{1}; i <= max;)
    {
        cb(i, state);

        j += i;
        i = j - i;
    }
}

} // namespace fast

namespace creel {

template <typename T, typename TState>
    requires std::integral<T>
void fib_seq(
    T const max, callback_t<T, TState> const cb, TState* const state) noexcept
{
    // Adapted from: https://youtu.be/IZc4Odd3K2Q?t=949
    for (T i{0}, j{1}; i <= max;)
    {
        cb(i, state);

        j = (i += j) - j;
    }
}

} // namespace creel

} // namespace forfun::fibonacci::sequence

#endif // FORFUN_FIBONACCI_SEQUENCE_HPP_
