// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/palindromic_number.hpp"

#include <cstdlib>

[[nodiscard]] /* constexpr */ bool is_palindrome(int const n) noexcept {
    if (n < 0) {
        return false;
    }

    int nn{0};
    std::div_t d{.quot = n, .rem = 0};
    while (d.quot > 0) {
        nn *= 10;
        d = std::div(d.quot, 10);
        nn += d.rem;
    }

    return n == nn;
}
