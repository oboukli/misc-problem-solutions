// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Palindromic_number

#ifndef FORFUN_PALINDROMIC_NUMBER_HPP_
#define FORFUN_PALINDROMIC_NUMBER_HPP_

#include <concepts>
#include <type_traits>

namespace forfun::palindromic_number {

namespace fast {

[[nodiscard]] constexpr auto
is_palindrome(std::integral auto const n) noexcept -> bool
{
    using T = std::remove_const_t<decltype(n)>;

    T nn{};
    auto d{n};
    while (d > T{0})
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        nn = (nn * T{10}) + (d % T{10});
        d /= T{10};
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    return n == nn;
}

} // namespace fast

namespace stl {

[[nodiscard]] auto is_palindrome(int n) noexcept -> bool;

} // namespace stl

} // namespace forfun::palindromic_number

#endif // FORFUN_PALINDROMIC_NUMBER_HPP_
