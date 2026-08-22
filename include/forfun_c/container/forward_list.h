/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#ifndef FORFUN_C_CONTAINER_FORWARD_LIST_H_
#define FORFUN_C_CONTAINER_FORWARD_LIST_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* defined(__GNUC__) || defined(__clang__) */

struct forfun_forward_list_node {
    struct forfun_forward_list_node* next;

    unsigned int value;
};

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* defined(__GNUC__) || defined(__clang__) */

void forfun_free_node_list(struct forfun_forward_list_node* node_ptr);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FORFUN_C_CONTAINER_FORWARD_LIST_H_ */
