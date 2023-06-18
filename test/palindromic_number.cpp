// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/palindromic_number.hpp"

#include <cassert>

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
