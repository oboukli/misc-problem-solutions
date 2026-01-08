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

namespace metaprogramming {

namespace classic {

template <int n, typename Result>
    requires std::integral<Result>
struct factorial {
    static constexpr Result value{n * factorial<n - 1, Result>::value};
};

template <typename Result>
    requires std::integral<Result>
struct factorial<0, Result> {
    static constexpr Result value{1};
};

template <int n, typename Result>
constexpr Result const factorial_v{factorial<n, Result>::value};

} // namespace classic

namespace modern {

using std::multiplies;

template <typename A, typename B, typename Result>
    requires std::integral<Result>
struct multiplication {
    static constexpr Result const value{
        multiplies<Result>{}(A::value, B::value)
    };
};

template <int n, typename Result>
    requires std::integral<Result>
struct factorial {
    // clang-format off
    static constexpr Result const value{
        std::conditional_t<
            n <= 1,
            std::integral_constant<Result, 1>,
            multiplication<
                std::integral_constant<Result, n>,
                factorial<n - 1, Result>,
                Result
            >
        >::value};
    // clang-format on
};

template <int n, typename Result>
constexpr Result const factorial_v{factorial<n, Result>::value};

} // namespace modern

} // namespace metaprogramming

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
