/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/mem/mem.h"

#include <stddef.h>
#include <stdlib.h>

static forfun_mem forfun_mem_;

void forfun_mem_set(forfun_mem const mem)
{
    forfun_mem_.ff_malloc = mem.ff_malloc;
    forfun_mem_.ff_free = mem.ff_free;
}

forfun_mem forfun_mem_get(void)
{
    forfun_mem mem;
    mem.ff_malloc = forfun_mem_.ff_malloc;
    mem.ff_free = forfun_mem_.ff_free;

    return mem;
}

void forfun_mem_reset_to_default(void)
{
    forfun_mem_.ff_malloc = &malloc;
    forfun_mem_.ff_free = &free;
}
