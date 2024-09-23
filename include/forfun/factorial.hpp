// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Factorial

#ifndef FORFUN_FACTORIAL_HPP_
#define FORFUN_FACTORIAL_HPP_

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <ranges>
#include <type_traits>

#include "common.hpp"

namespace forfun::factorial {

namespace iterative {

/// @note Providing a negative argument for @p n results in undefined behavior.
/// @note For large values of @p n, the result may overflow the return type.
[[nodiscard]] constexpr auto factorial(std::integral auto const n) noexcept
    -> decltype(n)
{
    using T = std::remove_const_t<decltype(n)>;

    assert(n >= T{0});

    T result{1};
    for (auto i{n}; i > T{1}; --i)
    {
        result *= i;
    }

    return result;
}

} // namespace iterative

namespace recursive {

/// @note Providing a negative argument for @p n results in undefined behavior.
template <common::concepts::addition_unpromoted T>
[[nodiscard]] constexpr auto factorial(T const n) noexcept -> T
{
    assert(n >= T{0});

    if (n <= T{1})
    {
        return T{1};
    }

    return n * factorial(n - T{1});
}

} // namespace recursive

namespace stl_functional {

/// @note Providing a negative argument for @p n results in undefined behavior.
/// @note For large values of @p n, the result may overflow the return type.
[[nodiscard]] constexpr auto factorial(std::integral auto const n) noexcept
{
    using T = decltype(n);

    assert(n >= T{0});

    return std::ranges::fold_left(
        std::views::iota(T{1}) | std::views::take(n), T{1}, std::multiplies<>()
    );
}

} // namespace stl_functional

} // namespace forfun::factorial

#endif // FORFUN_FACTORIAL_HPP_
