/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/container/forward_list.h"

#include <stddef.h>

#include "forfun_c/mem/mem.h"

void forfun_free_node_list(struct forfun_forward_list_node* const root_node_ptr)
{
    struct forfun_forward_list_node const* node_ptr = root_node_ptr;
    while (node_ptr != NULL)
    {
        struct forfun_forward_list_node* aux = node_ptr->next;

        g_forfun_mem.ff_free((void*)node_ptr);

        node_ptr = aux;
    }
}
