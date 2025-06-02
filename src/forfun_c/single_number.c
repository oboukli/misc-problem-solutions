/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/single_number.h"

#include <stddef.h>

int forfun_get_single(int const* nums, size_t const nums_size)
{
    int result = 0;
    size_t i = 0UL;

    while (i++ < nums_size)
    {
        result ^= *nums;
        ++nums;
    }

    return result;
}
