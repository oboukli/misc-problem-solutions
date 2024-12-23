// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/forward_list.hpp"

TEST_CASE("Forward list", "[container][forward_list][dynamic_allocation]")
{
    SECTION("Forward list is initially empty")
    {
        forfun::experimental::container::forward_list<int> const forward_list{};

        REQUIRE(forward_list.empty());
    }

    SECTION("Push front one element (benchmark case)")
    {
        forfun::experimental::container::forward_list<int> forward_list{};

        REQUIRE(forward_list.empty());

        forward_list.push_front(1301);

        REQUIRE(forward_list.front() == 1301);
        REQUIRE_FALSE(forward_list.empty());
    }

    SECTION("Push front two elements")
    {
        forfun::experimental::container::forward_list<int> forward_list{};

        REQUIRE(forward_list.empty());

        forward_list.push_front(1303);

        REQUIRE(forward_list.front() == 1303);
        REQUIRE_FALSE(forward_list.empty());

        forward_list.push_front(1307);

        REQUIRE(forward_list.front() == 1307);
        REQUIRE_FALSE(forward_list.empty());
    }

    SECTION("Push front three elements")
    {
        forfun::experimental::container::forward_list<int> forward_list{};

        REQUIRE(forward_list.empty());

        forward_list.push_front(1319);

        REQUIRE(forward_list.front() == 1319);

        forward_list.push_front(1321);

        REQUIRE(forward_list.front() == 1321);

        forward_list.push_front(1327);

        REQUIRE(forward_list.front() == 1327);
        REQUIRE_FALSE(forward_list.empty());
    }

    SECTION("Push front four elements")
    {
        forfun::experimental::container::forward_list<int> forward_list{};

        REQUIRE(forward_list.empty());

        forward_list.push_front(1361);

        REQUIRE(forward_list.front() == 1361);
        REQUIRE_FALSE(forward_list.empty());

        forward_list.push_front(1021);

        REQUIRE(forward_list.front() == 1021);

        forward_list.push_front(1367);

        REQUIRE(forward_list.front() == 1367);

        forward_list.push_front(1373000);

        REQUIRE(forward_list.front() == 1373000);
        REQUIRE_FALSE(forward_list.empty());
    }

    SECTION("Pop back one element out of empty list")
    {
        forfun::experimental::container::forward_list<int> forward_list{};

        forward_list.pop_front();

        REQUIRE(forward_list.empty());
    }

    SECTION("Pop back one element out of list of one element")
    {
        forfun::experimental::container::forward_list<int> forward_list{};
        forward_list.push_front(1381);

        forward_list.pop_front();

        REQUIRE(forward_list.empty());
    }

    SECTION("Pop back one element out of list of two elements")
    {
        forfun::experimental::container::forward_list<int> forward_list{};
        forward_list.push_front(1399);
        forward_list.push_front(1409);

        forward_list.pop_front();

        REQUIRE_FALSE(forward_list.empty());
        REQUIRE(forward_list.front() == 1399);
    }

    SECTION("Pop back one element out of list of three elements")
    {
        forfun::experimental::container::forward_list<int> forward_list{};
        forward_list.push_front(1399);
        forward_list.push_front(1409);
        forward_list.push_front(1423);

        forward_list.pop_front();

        REQUIRE_FALSE(forward_list.empty());
        REQUIRE(forward_list.front() == 1409);
    }

    SECTION("Clear empty list")
    {
        forfun::experimental::container::forward_list<int> forward_list{};

        forward_list.clear();

        REQUIRE(forward_list.empty());
    }

    SECTION("Clear list of one")
    {
        forfun::experimental::container::forward_list<int> forward_list{};
        forward_list.push_front(5);

        REQUIRE_FALSE(forward_list.empty());

        forward_list.clear();

        REQUIRE(forward_list.empty());
    }

    SECTION("Clear list of three")
    {
        forfun::experimental::container::forward_list<int> forward_list{};
        forward_list.push_front(5);
        forward_list.push_front(7);
        forward_list.push_front(11);

        REQUIRE_FALSE(forward_list.empty());

        forward_list.clear();

        REQUIRE(forward_list.empty());
    }

    SECTION("Method front() returns a reference")
    {
        forfun::experimental::container::forward_list<int> forward_list{};

        REQUIRE(forward_list.empty());

        forward_list.push_front(1399);

        REQUIRE(forward_list.front() == 1399);

        forward_list.front() = 1400;

        REQUIRE(forward_list.front() == 1400);
    }
}
