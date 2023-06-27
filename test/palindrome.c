/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun/palindrome.h"

#include <assert.h>
#include <string.h>

void test_palindrome() {
    {
        char const* const s = "";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "\xb8Y\xb8";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "aa";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "aba";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "a b a";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "101";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "tattarrattat";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "dummy";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome(s, len);
        assert(f_palindrome == 0);
    }
}

void test_palindrome_ci() {
    {
        char const* const s = "Aa";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome_ci(s, len);
        assert(f_palindrome);
    }

    {
        char const* const s = "Aab4'{x{'4BaA";
        size_t const len = strlen(s);
        int const f_palindrome = is_palindrome_ci(s, len);
        assert(f_palindrome);
    }
}

int main() {
    test_palindrome();

    test_palindrome_ci();

    return 0;
}
