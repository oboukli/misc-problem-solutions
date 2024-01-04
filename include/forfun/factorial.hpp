// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Factorial

#ifndef FORFUN_FACTORIAL_HPP_
#define FORFUN_FACTORIAL_HPP_

#include <cassert>
#include <concepts>
#include <type_traits>

namespace forfun::factorial {

namespace iterative {

/// @note Providing a negative argument for @p n results in undefined behavior.
/// @note For large values of @p n, the result may overflow the return type.
[[nodiscard]] constexpr inline auto
factorial(std::integral auto const n) noexcept -> decltype(n)
{
    using T = std::remove_const<decltype(n)>::type;

    assert(n >= T{0});

    auto result{T{1}};
    for (auto i{n}; i > T{1}; --i)
    {
        result *= i;
    }

    return result;
}

} // namespace iterative

} // namespace forfun::factorial

#endif // FORFUN_FACTORIAL_HPP_
