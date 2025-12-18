/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/shim/allocator.h"

#include <stddef.h>

#include <mimalloc.h>

#include "forfun_c/common.h"
#include "forfun_c/mem/mem.h"

struct forfun_shim_context {
    size_t shim_malloc_call_count;

    size_t shim_free_call_count;

    size_t shim_malloc_fail_after;
};

static struct forfun_mem g_unshimmed_mem_ = {NULL, NULL};
static struct forfun_shim_context g_shim_context_
    = {0, 0, (size_t)-1 /* SIZE_MAX in C99 */};
static int g_shim_is_enabled_ = FORFUN_FALSE;

int forfun_shim_enable(void)
{
    struct forfun_mem mem;

    if (g_shim_is_enabled_ == FORFUN_TRUE)
    {
        /* Error: shim is already initialized. */
        return FORFUN_SHIM_ERROR;
    }

    mem.ff_malloc = forfun_shim_malloc;
    mem.ff_free = forfun_shim_free;

    g_unshimmed_mem_ = forfun_mem_get();

    forfun_mem_set(mem);

    g_shim_is_enabled_ = FORFUN_TRUE;

    return FORFUN_SHIM_OK;
}

void forfun_shim_disable(void)
{
    forfun_mem_set(g_unshimmed_mem_);

    g_shim_is_enabled_ = FORFUN_FALSE;
}

int forfun_shim_is_enabled(void)
{
    return g_shim_is_enabled_;
}

void forfun_shim_reset(void)
{
    g_shim_context_.shim_malloc_call_count = 0;
    g_shim_context_.shim_free_call_count = 0;
    g_shim_context_.shim_malloc_fail_after = (size_t)-1; /* SIZE_MAX in C99 */
}

size_t forfun_shim_get_malloc_call_count(void)
{
    return g_shim_context_.shim_malloc_call_count;
}

size_t forfun_shim_get_free_call_count(void)
{
    return g_shim_context_.shim_free_call_count;
}

size_t forfun_shim_get_malloc_fail_after(void)
{
    return g_shim_context_.shim_malloc_fail_after;
}

void forfun_shim_set_malloc_fail_after(size_t const fail_after)
{
    g_shim_context_.shim_malloc_fail_after = fail_after;
}

void* forfun_shim_malloc(size_t const size)
{
    ++g_shim_context_.shim_malloc_call_count;

    if ((g_shim_context_.shim_malloc_fail_after
         != (size_t)-1 /* SIZE_MAX in C99 */)
        && (g_shim_context_.shim_malloc_call_count
            > g_shim_context_.shim_malloc_fail_after))
    {
        return NULL;
    }

    return mi_malloc(size);
}

void forfun_shim_free(void* const ptr)
{
    ++g_shim_context_.shim_free_call_count;

    mi_free(ptr);
}
