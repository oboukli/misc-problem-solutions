// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/forward_list_cycle.hpp"
#include "forfun/container/forward_list_node.hpp"

TEST_CASE("Forward list cycle", "[forward_list_cycle]")
{
    using forfun::container::forward_list_cycle::has_cycle;

    using NodeType = forfun::container::forward_list_node<int>;

    SECTION("Null pointer")
    {
        STATIC_REQUIRE_FALSE(has_cycle<int>(nullptr));
    }

    SECTION("One disconnected node")
    {
        static constexpr NodeType const head{101};

        STATIC_REQUIRE_FALSE(has_cycle(&head));
    }
}
