// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifdef _WIN32

#include <mimalloc.h>

#include <catch2/catch_test_macros.hpp>

#include "forfun/runtime/allocator_config.hpp" // IWYU pragma: keep

TEST_CASE("Runtime checks for mimalloc", "[allocator_config]")
{
    REQUIRE(mi_is_redirected());
}

#endif // _WIN32
