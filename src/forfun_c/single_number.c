/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/single_number.h"

#include <stddef.h>

int forfun_s1_get_single(int const* const nums, size_t const nums_size)
{
    unsigned int result = 0U;

    size_t i;

    for (i = 0; i < nums_size; ++i)
    {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif /* __clang__ */

        result ^= (unsigned int)nums[i];

#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */
    }

    return (int)result;
}

int forfun_s2_get_single(int const* nums, size_t nums_size)
{
    unsigned int result = 0U;

    while (nums_size)
    {
        result ^= (unsigned int)*nums;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif /* __clang__ */

        ++nums;

#ifdef __clang__
#pragma clang diagnostic pop
#endif /* __clang__ */

        --nums_size;
    }

    return (int)result;
}
