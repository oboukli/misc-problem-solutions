// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Factorial

#ifndef FORFUN_FACTORIAL_HPP_
#define FORFUN_FACTORIAL_HPP_

#include <algorithm>
#include <cassert>
#include <concepts>
#include <functional>
#include <ranges>
#include <type_traits>

#include "forfun/common/concepts.hpp"

namespace forfun::factorial {

namespace iterative {

/// @note Assumes @p n to be non-negative, otherwise the behavior of the
/// strategy is undefined.
///
/// @note For large values of @p n, the result may overflow the return type.
[[nodiscard]] constexpr auto factorial(std::integral auto const n) noexcept
    -> decltype(n)
{
    using T = std::remove_const_t<decltype(n)>;

    assert(n >= T{});

    T result{1};
    for (auto i{n}; i > T{1}; --i)
    {
        result *= i;
    }

    return result;
}

} // namespace iterative

namespace recursive {

/// @note Assumes @p n to be non-negative, otherwise the behavior of the
/// strategy is undefined.
template <common::concepts::addition_unpromoted T>
[[nodiscard]] constexpr auto factorial(T const n) noexcept -> T
{
    assert(n >= T{});

    if (n <= T{1}) [[unlikely]]
    {
        return T{1};
    }

    return n * factorial(n - T{1});
}

} // namespace recursive

namespace stl_functional {

/// @note Assumes @p n to be non-negative, otherwise the behavior of the
/// strategy is undefined.
///
/// @note For large values of @p n, the result may overflow the return type.
[[nodiscard]] constexpr auto factorial(std::integral auto const n) noexcept
{
    using T = decltype(n);

    assert(n >= T{});

    return std::ranges::fold_left(
        std::views::iota(T{1}) | std::views::take(n), T{1}, std::multiplies{}
    );
}

} // namespace stl_functional

} // namespace forfun::factorial

#endif // FORFUN_FACTORIAL_HPP_
