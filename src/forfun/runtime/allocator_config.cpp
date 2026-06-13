// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/runtime/allocator_config.hpp" // IWYU pragma: keep

// Override the C++ new and delete operations.
#include <mimalloc-new-delete.h> // IWYU pragma: keep
