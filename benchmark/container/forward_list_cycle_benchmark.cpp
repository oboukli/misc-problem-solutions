// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/container/forward_list_cycle.hpp"
#include "forfun/container/forward_list_node.hpp"

TEST_CASE("Forward list cycle benchmarking", "[benchmark][forward_list_cycle]")
{
    using namespace forfun::container;

    using NodeType = forfun::container::forward_list_node<int>;

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

    ankerl::nanobench::Bench()

        .title("Forward list cycle")
        .relative(true)

        .run(
            NAMEOF_RAW(forward_list_cycle::has_cycle<int>).c_str(),
            [&head] noexcept -> void {
                auto const volatile r{forward_list_cycle::has_cycle(&head)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
