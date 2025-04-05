// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iterator>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/list.hpp"

TEST_CASE("Linked list", "[container][list][dynamic_allocation]")
{
    SECTION("Iterator")
    {
        using forfun::experimental::container::list;

        STATIC_REQUIRE(std::bidirectional_iterator<list::iterator>);

        STATIC_REQUIRE(std::indirectly_writable<list::iterator, int>);
    }

    SECTION("Const iterator")
    {
        using forfun::experimental::container::list;

        STATIC_REQUIRE(std::bidirectional_iterator<list::const_iterator>);

        STATIC_REQUIRE_FALSE(
            std::indirectly_writable<list::const_iterator, int>
        );
    }
}
