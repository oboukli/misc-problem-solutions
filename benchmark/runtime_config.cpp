// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <mimalloc.h>

#include <catch2/catch_test_macros.hpp>

// This is not a test case. It is a workaround to load mimalloc.
TEST_CASE("Load mimalloc", "")
{
    [[maybe_unused]] auto const volatile dummy{::mi_version()};
}
