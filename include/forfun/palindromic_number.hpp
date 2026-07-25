// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Palindromic_number

#ifndef FORFUN_PALINDROMIC_NUMBER_HPP_
#define FORFUN_PALINDROMIC_NUMBER_HPP_

#include <concepts>
#include <type_traits>

namespace forfun::palindromic_number {

namespace fast {

[[nodiscard]] constexpr auto is_palindrome(std::integral auto const n) noexcept
    -> bool
{
    using T = std::remove_const_t<decltype(n)>;

    T reversed{};
    auto remaining{n};
    while (remaining > T{})
    {
        reversed = static_cast<T>((reversed * T{10}) + (remaining % T{10}));
        remaining /= T{10};
    }

    return n == reversed;
}

} // namespace fast

namespace stl {

[[nodiscard]] auto is_palindrome(int n) noexcept -> bool;

} // namespace stl

} // namespace forfun::palindromic_number

#endif // FORFUN_PALINDROMIC_NUMBER_HPP_
