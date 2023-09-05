// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Palindromic_number

#ifndef FORFUN_PALINDROMIC_NUMBER_HPP_
#define FORFUN_PALINDROMIC_NUMBER_HPP_

#include <concepts>

namespace forfun::palindromic_number {

namespace fast {

template <typename T>
    requires std::integral<T>
[[nodiscard]] constexpr bool is_palindrome(T const n) noexcept {
    T nn{};
    auto d{n};
    while (d > T{0}) {
        nn = (nn * T{10}) + d % T{10};
        d /= T{10};
    }

    return n == nn;
}

} // namespace fast

namespace stl {

[[nodiscard]] bool is_palindrome(int const n) noexcept;

} // namespace stl

} // namespace forfun::palindromic_number

#endif // FORFUN_PALINDROMIC_NUMBER_HPP_
