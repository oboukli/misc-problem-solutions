// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/palindromic_number.hpp"

#include <cstdlib>

namespace forfun::palindromic_number::stl {

[[nodiscard]] auto is_palindrome(int const n) noexcept -> bool
{
    int carried{};
    std::div_t division_result{.quot = n, .rem = 0};
    while (division_result.quot > 0)
    {
        division_result = std::div(division_result.quot, 10);
        carried = (carried * 10) + division_result.rem;
    }

    return n == carried;
}

} // namespace forfun::palindromic_number::stl
