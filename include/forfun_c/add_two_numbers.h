/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

/*
Problem reference:
https://leetcode.com/problems/add-two-numbers/description/
*/

#ifndef FORFUN_C_ADD_TWO_NUMBERS_H_
#define FORFUN_C_ADD_TWO_NUMBERS_H_

#include "forfun_c/container/forward_list.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

struct forfun_forward_list_node* forfun_iterative_add_two_numbers(
    struct forfun_forward_list_node const* addend_a,
    struct forfun_forward_list_node const* addend_b
);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FORFUN_C_ADD_TWO_NUMBERS_H_ */
