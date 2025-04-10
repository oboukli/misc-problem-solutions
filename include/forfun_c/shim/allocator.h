/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#ifndef FORFUN_C_SHIM_ALLOCATOR_H_
#define FORFUN_C_SHIM_ALLOCATOR_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

int forfun_shim_enable(void);

void forfun_shim_disable(void);

int forfun_shim_is_enabled(void);

void forfun_shim_reset(void);

size_t forfun_shim_get_malloc_call_count(void);

size_t forfun_shim_get_free_call_count(void);

size_t forfun_shim_get_malloc_fail_after(void);

void forfun_shim_set_malloc_fail_after(size_t fail_after);

void* forfun_shim_malloc(size_t size);

void forfun_shim_free(void* ptr);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FORFUN_C_SHIM_ALLOCATOR_H_ */
