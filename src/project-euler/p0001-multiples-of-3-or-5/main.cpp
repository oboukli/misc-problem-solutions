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

#include <algorithm>
#include <cassert>

namespace {
[[nodiscard]] inline constexpr int sum_2x(int const n, int const q) noexcept {
    auto const d = std::div(n, q);

    return d.quot * (q + n - d.rem);
}
} // namespace

[[nodiscard]] constexpr int find_sum_mult_three_five(int n) noexcept {
    --n;

    return (sum_2x(n, 3) + sum_2x(n, 5) - sum_2x(n, 15)) / 2;
}

int main() {
    {
        int const s{find_sum_mult_three_five(1)};
        assert(s == 0);
    }

    {
        int const s{find_sum_mult_three_five(4)};
        assert(s == 3);
    }

    {
        int s{find_sum_mult_three_five(6)};
        assert(s == 8);
    }

    {
        int const s{find_sum_mult_three_five(10)};
        assert(s == 23);
    }

    {
        int const s{find_sum_mult_three_five(11)};
        assert(s == 33);
    }

    {
        int s{find_sum_mult_three_five(1000)};
        assert(s == 233168);
    }

    return 0;
}
