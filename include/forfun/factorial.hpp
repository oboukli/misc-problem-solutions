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
#include <ranges>
#include <type_traits>
#include <utility>

namespace forfun::factorial {

namespace iterative {

/// @note Providing a negative argument for @p n results in undefined behavior.
/// @note For large values of @p n, the result may overflow the return type.
[[nodiscard]] constexpr inline auto
factorial(std::integral auto const n) noexcept -> decltype(n)
{
    using T = std::remove_const_t<decltype(n)>;

    assert(n >= T{0});

    auto result{T{1}};
    for (auto i{n}; i > T{1}; --i)
    {
        result *= i;
    }

    return result;
}

} // namespace iterative

namespace recursive {

/// @note Providing a negative argument for @p n results in undefined behavior.
template <std::integral T>
    requires std::is_same_v<T, decltype(std::declval<T>() + std::declval<T>())>
[[nodiscard]] constexpr inline T factorial(T const n) noexcept
{
    assert(n >= T{0});

    if (n <= T{1})
    {
        return T{1};
    }

    return n * factorial(n - T{1});
}

} // namespace recursive

#if __cpp_lib_ranges_fold >= 202207L

#define FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE true

namespace stl_functional {

/// @note Providing a negative argument for @p n results in undefined behavior.
/// @note For large values of @p n, the result may overflow the return type.
[[nodiscard]] constexpr inline auto
factorial(std::integral auto const n) noexcept
{
    using T = decltype(n);

    assert(n >= T{0});

    return std::ranges::fold_left(
        std::views::iota(T{1}) | std::views::take(n),
        T{1},
        std::multiplies<>());
}

} // namespace stl_functional

#endif // __cpp_lib_ranges_fold >= 202207L

} // namespace forfun::factorial

#endif // FORFUN_FACTORIAL_HPP_
