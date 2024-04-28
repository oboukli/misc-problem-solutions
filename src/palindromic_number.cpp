// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/palindromic_number.hpp"

#include <cstdlib>

namespace forfun::palindromic_number::stl {

[[nodiscard]] auto is_palindrome(int const n) noexcept -> bool
{
    int nn{0};
    std::div_t d{.quot = n, .rem = 0};
    while (d.quot > 0)
    {
        // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
        d = std::div(d.quot, 10);
        nn = (nn * 10) + d.rem;
        // NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
    }

    return n == nn;
}

} // namespace forfun::palindromic_number::stl
