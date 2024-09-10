/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/palindrome.h"

#include <ctype.h>
#include <stddef.h>

/* Adhere to C89/C90, for the fun of it. */

#if __clang__
#pragma clang attribute push( \
    __attribute__(( \
        no_sanitize("pointer-overflow", "unsigned-integer-overflow") \
    )), \
    apply_to = function \
)
#endif /* __clang__ */
int forfun_is_palindrome(char const* str, size_t const length)
{
    char const* const mid = str + (length / 2U);

    /* Two insulated and harmless overflows when length is zero. */
    char const* str_rhs = str + (length - 1U);

    for (; str != mid; ++str)
    {
        if (*str != *str_rhs)
        {
            return 0;
        }

        --str_rhs;
    }

    return 1;
}
#if __clang__
#pragma clang attribute pop
#endif /* __clang__ */

#if __clang__
#pragma clang attribute push( \
    __attribute__(( \
        no_sanitize("pointer-overflow", "unsigned-integer-overflow") \
    )), \
    apply_to = function \
)
#endif /* __clang__ */
int forfun_is_palindrome_ci(char const* str, size_t const length)
{
    char const* const mid = str + (length / 2U);

    /* Two insulated and harmless overflows when length is zero. */
    char const* str_rhs = str + (length - 1U);

    for (; str != mid; ++str)
    {
        if (tolower((unsigned char)(*str))
            != tolower((unsigned char)(*str_rhs)))
        {
            return 0;
        }

        --str_rhs;
    }

    return 1;
}
#if __clang__
#pragma clang attribute pop
#endif /* __clang__ */
