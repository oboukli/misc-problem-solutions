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

struct forfun_internal_result {
    struct forfun_forward_list_node* node;
    int error;
};

static struct forfun_internal_result forfun_do_add_two_numbers(
    struct forfun_forward_list_node const* addend_a,
    struct forfun_forward_list_node const* addend_b,
    unsigned int carry
);

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

        aux_node_ptr->value = sum % 10U;

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

static struct forfun_internal_result forfun_do_add_two_numbers(
    struct forfun_forward_list_node const* const addend_a,
    struct forfun_forward_list_node const* const addend_b,
    unsigned int const carry
)
{
    struct forfun_internal_result result = {NULL, 0};
    unsigned int sum = carry;

    unsigned int const val_a = addend_a == NULL ? 0U : addend_a->value;
    unsigned int const val_b = addend_b == NULL ? 0U : addend_b->value;

    assert(val_a <= 9U);
    assert(val_b <= 9U);

    sum += val_a + val_b;

    if ((carry != 0U) || (addend_a != NULL) || (addend_b != NULL))
    {
        struct forfun_forward_list_node* aux_node_ptr;
        struct forfun_internal_result next_result;
        struct forfun_forward_list_node* next_a
            = addend_a == NULL ? NULL : addend_a->next;
        struct forfun_forward_list_node* next_b
            = addend_b == NULL ? NULL : addend_b->next;

        aux_node_ptr = (struct forfun_forward_list_node*)malloc(
            sizeof(struct forfun_forward_list_node)
        );
        if (aux_node_ptr == NULL)
        {
            goto error;
        }

        aux_node_ptr->value = sum % 10U;
        next_result = forfun_do_add_two_numbers(next_a, next_b, sum / 10U);
        if (next_result.error == 1)
        {
            free(aux_node_ptr);

            goto error;
        }

        aux_node_ptr->next = next_result.node;
        result.node = aux_node_ptr;
    }

    return result;

error:
    result.error = 1;

    return result;
}

struct forfun_forward_list_node* forfun_recursive_add_two_numbers(
    struct forfun_forward_list_node const* const addend_a,
    struct forfun_forward_list_node const* const addend_b
)
{
    struct forfun_internal_result result;
    result = forfun_do_add_two_numbers(addend_a, addend_b, 0U);

    if (result.error == 1)
    {
        forfun_free_node_list(result.node);

        return NULL;
    }

    assert(result.error == 0);
    assert(result.node != NULL);

    return result.node;
}
