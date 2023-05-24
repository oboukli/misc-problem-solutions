// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

// Problem source:
// https://en.wikipedia.org/wiki/Palindromic_number

#include <cassert>
#include <cstdlib>

[[nodiscard]] bool is_palindrome(const int n) noexcept {
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

int main() {
    {
        bool const f_palindrome{is_palindrome(0)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(1)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(11)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(121)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(212)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(333)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(4444)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(14341)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(143341)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(4268624)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome(-1)};
        assert(f_palindrome == false);
    }

    {
        bool const f_palindrome{is_palindrome(12)};
        assert(f_palindrome == false);
    }

    {
        bool const f_palindrome{is_palindrome(12345)};
        assert(f_palindrome == false);
    }

    {
        bool const f_palindrome{is_palindrome(4268604)};
        assert(f_palindrome == false);
    }

    return 0;
}
