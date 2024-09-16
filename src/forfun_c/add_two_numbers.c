/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#include "forfun_c/add_two_numbers.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

#include "forfun_c/container/forward_list.h"

struct forfun_forward_list_node* forfun_iterative_add_two_numbers(
    struct forfun_forward_list_node const* addend_a,
    struct forfun_forward_list_node const* addend_b
)
{
    unsigned int sum = 0U;
    struct forfun_forward_list_node* aux_node_ptr
        = (struct forfun_forward_list_node*)malloc(
            sizeof(struct forfun_forward_list_node)
        );
    struct forfun_forward_list_node* const root_node_ptr = aux_node_ptr;
    if (aux_node_ptr == NULL)
    {
        return NULL;
    }

    aux_node_ptr->next = NULL;

    for (;;)
    {
        if (addend_a != NULL)
        {
            assert(addend_a->value <= 9U);
            sum += addend_a->value;
            addend_a = addend_a->next;
        }

        if (addend_b != NULL)
        {
            assert(addend_b->value <= 9U);
            sum += addend_b->value;
            addend_b = addend_b->next;
        }

        /* NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers) */
        aux_node_ptr->value = sum % 10U;

        /* NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers) */
        sum = sum / 10U;

        if ((addend_a == NULL) && (addend_b == NULL) && (sum == 0U))
        {
            assert(root_node_ptr != NULL);
            return root_node_ptr;
        }

        aux_node_ptr->next = (struct forfun_forward_list_node*)malloc(
            sizeof(struct forfun_forward_list_node)
        );
        aux_node_ptr = aux_node_ptr->next;
        if (aux_node_ptr == NULL)
        {
            break;
        }
        aux_node_ptr->next = NULL;
    }

    forfun_free_node_list(root_node_ptr);

    return NULL;
}
