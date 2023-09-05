// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Palindromic_number

#ifndef FORFUN_PALINDROMIC_NUMBER_HPP_
#define FORFUN_PALINDROMIC_NUMBER_HPP_

namespace forfun::palindromic_number {

namespace fast {

[[nodiscard]] constexpr bool is_palindrome(int const n) noexcept {
    int nn{0};
    int d{n};
    while (d > 0) {
        nn = (nn * 10) + d % 10;
        d /= 10;
    }

    return n == nn;
}

} // namespace fast

namespace stl {

[[nodiscard]] bool is_palindrome(int const n) noexcept;

} // namespace stl

} // namespace forfun::palindromic_number

#endif // FORFUN_PALINDROMIC_NUMBER_HPP_
