/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/single_number.h"

#include <stddef.h>

int forfun_get_single(int const* nums, size_t nums_size)
{
    unsigned int result = 0U;

    while (nums_size)
    {
        result ^= (unsigned int)*nums;
        ++nums;
        --nums_size;
    }

    return (int)result;
}
