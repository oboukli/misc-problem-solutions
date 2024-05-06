/*
Copyright (c) Omar Boukli-Hacene. All rights reserved.
Distributed under an MIT-style license that can be
found in the LICENSE file.
*/

/* SPDX-License-Identifier: MIT */

/*
Problem reference:
https://en.wikipedia.org/wiki/Palindrome
*/

#ifndef FORFUN_C_PALINDROME_H_
#define FORFUN_C_PALINDROME_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stddef.h>

int is_palindrome(char const* str, size_t size);

int is_palindrome_ci(char const* str, size_t size);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FORFUN_C_PALINDROME_H_ */
