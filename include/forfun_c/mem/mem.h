/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#ifndef FORFUN_C_MEM_MEM_H_
#define FORFUN_C_MEM_MEM_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

struct forfun_mem {
    void* (*ff_malloc)(size_t);

    void (*ff_free)(void*);
};

extern struct forfun_mem g_forfun_mem;

void forfun_mem_set(struct forfun_mem mem);

struct forfun_mem forfun_mem_get(void);

void forfun_mem_reset_to_default(void);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FORFUN_C_MEM_MEM_H_ */
