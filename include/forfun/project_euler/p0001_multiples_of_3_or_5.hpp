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

[[nodiscard]] constexpr int find_sum_mult_three_five(int n) noexcept;

namespace detail {

[[nodiscard]] inline constexpr int sum_2x(int const n, int const q) noexcept
{
    return (n / q) * (q + n - (n % q));
}

} // namespace detail

[[nodiscard]] constexpr int find_sum_mult_three_five(int n) noexcept
{
    using detail::sum_2x;

    --n;

    return (sum_2x(n, 3) + sum_2x(n, 5) - sum_2x(n, 15)) / 2;
}

} // namespace forfun::project_euler::multiples_of_3_or_5

#endif // FORFUN_PROJECT_EULER_P0001_MULTIPLES_OF_3_OR_5_HPP_
