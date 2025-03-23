// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://projecteuler.net/problem=1
///
/// Original problem text:
/// If we list all the natural numbers below 10 that are multiples of 3 or 5, we
/// get 3, 5, 6 and 9. The sum of these multiples is 23.
///
/// Find the sum of all the multiples of 3 or 5 below 1000.

#ifndef FORFUN_PROJECT_EULER_P0001_MULTIPLES_OF_3_OR_5_HPP_
#define FORFUN_PROJECT_EULER_P0001_MULTIPLES_OF_3_OR_5_HPP_

namespace forfun::project_euler::multiples_of_3_or_5 {

namespace detail {

/// Calculate the doubled sum of all multiples of q up to n.
///
/// Calculate, using a closed-form expression, the 2x value, avoiding premature
/// division by two operation.
///
/// @param q Base whose multiples to be calculated
/// @param n Upper inclusive limit
/// @return Result
#if defined(__GNUC__) or defined(__clang__) // The following guard breaks MSVC.
#if __has_cpp_attribute(gnu::const)
[[gnu::const]]
#endif // __has_cpp_attribute(gnu::const)
#endif // defined(__GNUC__) or defined(__clang__)
[[nodiscard]] constexpr auto
sum_mult_2x(unsigned int const q, unsigned int const n) noexcept -> unsigned int
{
    return (n / q) * (q + n - (n % q));
}

} // namespace detail

/// Find the sum of all the multiples of 3 or 5 up to n.
///
/// @param n Upper inclusive limit
/// @return Result
#if __has_cpp_attribute(gnu::flatten)
[[gnu::flatten]]
#endif // __has_cpp_attribute(gnu::flatten)
#if __has_cpp_attribute(msvc::forceinline_calls)
[[msvc::forceinline_calls]]
#endif // __has_cpp_attribute(msvc::forceinline_calls)
[[nodiscard]] constexpr auto
find_sum_mult_three_five(unsigned int const n) noexcept -> unsigned int
{
    using detail::sum_mult_2x;

    return (sum_mult_2x(3U, n) + sum_mult_2x(5U, n) - sum_mult_2x(15U, n)) / 2U;
}

} // namespace forfun::project_euler::multiples_of_3_or_5

#endif // FORFUN_PROJECT_EULER_P0001_MULTIPLES_OF_3_OR_5_HPP_
