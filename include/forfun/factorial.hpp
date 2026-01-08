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

namespace forfun::factorial {

namespace iterative {

/// @note Assumes @p n to be non-negative, otherwise the behavior of the
/// strategy is undefined.
///
/// @note For large values of @p n, the result may overflow the return type.
template <typename Result>
    requires std::integral<Result>
[[nodiscard]] constexpr auto factorial(int const n) noexcept -> Result
{
    assert(n >= 0);

    Result result{1};
    for (int i{n}; i > 1; --i)
    {
        result *= static_cast<Result>(i);
    }

    return result;
}

} // namespace iterative

namespace recursive {

/// @note Assumes @p n to be non-negative, otherwise the behavior of the
/// strategy is undefined.
template <typename Result>
    requires std::integral<Result>
[[nodiscard]] constexpr auto factorial(int const n) noexcept -> Result
{
    assert(n >= 0);

    if (n <= 1) [[unlikely]]
    {
        return Result{1};
    }

    return static_cast<Result>(n) * factorial<Result>(n - 1);
}

} // namespace recursive

namespace stl_functional {

/// @note Assumes @p n to be non-negative, otherwise the behavior of the
/// strategy is undefined.
///
/// @note For large values of @p n, the result may overflow the return type.
template <typename Result>
    requires std::integral<Result>
[[nodiscard]] constexpr auto factorial(int const n) noexcept -> Result
{
    assert(n >= 0);

    return std::ranges::fold_left(
        std::views::iota(Result{1}) | std::views::take(n),
        Result{1},
        std::multiplies<Result>{}
    );
}

} // namespace stl_functional

} // namespace forfun::factorial

#endif // FORFUN_FACTORIAL_HPP_
