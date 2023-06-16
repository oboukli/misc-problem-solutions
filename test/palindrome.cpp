// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/palindrome.hpp"

#include <cassert>

int main() {
    using namespace std::string_literals;

    {
        bool const f_palindrome{is_palindrome(""s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("\xb8Y\xb8"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("aa"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("aba"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("a b a"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("101"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("Aa"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("Aab4'{x{'4BaA"s)};
        assert(f_palindrome);
    }

    {
        bool const f_palindrome{is_palindrome("dummy"s)};
        assert(f_palindrome == false);
    }

    return 0;
}
