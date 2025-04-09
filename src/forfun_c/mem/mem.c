/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/mem/mem.h"

#include <stddef.h>
#include <stdlib.h>

forfun_mem g_forfun_mem;

void forfun_mem_set(forfun_mem const mem)
{
    g_forfun_mem.ff_malloc = mem.ff_malloc;
    g_forfun_mem.ff_free = mem.ff_free;
}

forfun_mem forfun_mem_get(void)
{
    forfun_mem mem;
    mem.ff_malloc = g_forfun_mem.ff_malloc;
    mem.ff_free = g_forfun_mem.ff_free;

    return mem;
}

void forfun_mem_reset_to_default(void)
{
    g_forfun_mem.ff_malloc = &malloc;
    g_forfun_mem.ff_free = &free;
}
