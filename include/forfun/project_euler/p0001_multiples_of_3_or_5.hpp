// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
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

[[nodiscard]] constexpr auto
sum_mult_2x(unsigned int const q, unsigned int const n) noexcept -> unsigned int
{
    return (n / q) * (q + n - (n % q));
}

} // namespace detail

[[nodiscard]] constexpr auto
find_sum_mult_three_five(unsigned int const n) noexcept -> unsigned int
{
    using detail::sum_mult_2x;

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers)
    return (sum_mult_2x(3U, n) + sum_mult_2x(5U, n) - sum_mult_2x(15U, n)) / 2U;
}

} // namespace forfun::project_euler::multiples_of_3_or_5

#endif // FORFUN_PROJECT_EULER_P0001_MULTIPLES_OF_3_OR_5_HPP_
