// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/forward_list.hpp"

TEST_CASE("Forward list", "[container][forward_list]")
{
    SECTION("Forward list is initially empty")
    {
        constexpr forfun::experimental::container::forward_list<int> const
            forward_list{};

        STATIC_REQUIRE(forward_list.empty());
    }
}
