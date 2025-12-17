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
        REQUIRE_FALSE(has_cycle<int>(nullptr));
    }

    SECTION("One disconnected node")
    {
        NodeType const head{101};

        REQUIRE_FALSE(has_cycle(&head));
    }

    SECTION("One self-referencing node")
    {
        NodeType head{103};

        head.next_ = &head;

        REQUIRE(has_cycle(&head));
    }

    SECTION("Two nodes forming a cycle")
    {
        NodeType head{107};
        NodeType n2{109};

        head.next_ = &n2;
        n2.next_ = &head;

        REQUIRE(has_cycle(&head));
    }

    SECTION("Two nodes without a cycle")
    {
        NodeType head{113};
        NodeType n2{127};

        head.next_ = &n2;

        REQUIRE_FALSE(has_cycle(&head));
    }

    SECTION("Three nodes with a cycle")
    {
        NodeType head{131};
        NodeType n2{137};
        NodeType n3{139};

        head.next_ = &n2;
        n2.next_ = &n3;
        n3.next_ = &head;

        REQUIRE(has_cycle(&head));
    }

    SECTION("Three nodes without a cycle")
    {
        NodeType head{149};
        NodeType n2{151};
        NodeType n3{157};

        head.next_ = &n2;
        n2.next_ = &n3;

        REQUIRE_FALSE(has_cycle(&head));
    }

    SECTION("Four nodes with a cycle")
    {
        NodeType head{163};
        NodeType n2{167};
        NodeType n3{179};
        NodeType n4{181};

        head.next_ = &n2;
        n2.next_ = &n3;
        n3.next_ = &n4;
        n4.next_ = &n2;

        REQUIRE(has_cycle(&head));
    }

    SECTION("Four nodes without a cycle")
    {
        NodeType head{191};
        NodeType n2{193};
        NodeType n3{197};
        NodeType n4{199};

        head.next_ = &n2;
        n2.next_ = &n3;
        n3.next_ = &n4;

        REQUIRE_FALSE(has_cycle(&head));
    }

    SECTION("Eight nodes with a cycle (benchmark case)")
    {
        NodeType head{211};
        NodeType n2{223};
        NodeType n3{227};
        NodeType n4{229};
        NodeType n5{233};
        NodeType n6{239};
        NodeType n7{241};
        NodeType n8{251};

        head.next_ = &n2;
        n2.next_ = &n3;
        n3.next_ = &n4;
        n4.next_ = &n5;
        n5.next_ = &n6;
        n6.next_ = &n7;
        n7.next_ = &n8;
        n8.next_ = &head;

        REQUIRE(has_cycle(&head));
    }
}
