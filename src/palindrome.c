/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun/palindrome.h"

#include <ctype.h>

int is_palindrome(char const* const str, size_t const size)
{
    size_t const mid = size / 2;

    size_t i;
    for (i = 0; i < mid; ++i)
    {
        if (str[i] != str[size - 1 - i])
        {
            return 0;
        }
    }

    return 1;
}

int is_palindrome_ci(char const* const str, size_t const size)
{
    size_t const mid = size / 2;

    size_t i;
    for (i = 0; i < mid; ++i)
    {
        if (tolower((unsigned char)str[i])
            != tolower((unsigned char)str[size - 1 - i]))
        {
            return 0;
        }
    }

    return 1;
}
