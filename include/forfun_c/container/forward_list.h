/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

#ifndef FORFUN_C_CONTAINER_FORWARD_LIST_HPP_
#define FORFUN_C_CONTAINER_FORWARD_LIST_HPP_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct forfun_forward_list_node {
    struct forfun_forward_list_node* next;

    unsigned int value;
};

void forfun_free_node_list(struct forfun_forward_list_node* root_node_ptr);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FORFUN_C_CONTAINER_FORWARD_LIST_HPP_ */
