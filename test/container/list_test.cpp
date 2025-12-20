// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/list.hpp"

TEST_CASE("Linked list", "[container][list][dynamic_allocation]")
{
    SECTION("List is initially empty")
    {
        forfun::experimental::container::list const some_list{};

        REQUIRE(some_list.empty());
    }

    SECTION("List's initial size is zero")
    {
        forfun::experimental::container::list const some_list{};

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
    }

    SECTION("Push back one element (benchmark case)")
    {
        forfun::experimental::container::list some_list{};

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());

        some_list.push_back(1301);

        REQUIRE(some_list.front() == 1301);
        REQUIRE(some_list.back() == 1301);
        REQUIRE(some_list.size() == 1UZ);
        REQUIRE_FALSE(some_list.empty());
    }

    SECTION("Push back two elements")
    {
        forfun::experimental::container::list some_list{};

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());

        some_list.push_back(1303);

        REQUIRE(some_list.front() == 1303);
        REQUIRE(some_list.back() == 1303);
        REQUIRE(some_list.size() == 1UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.push_back(1307);

        REQUIRE(some_list.front() == 1303);
        REQUIRE(some_list.back() == 1307);
        REQUIRE(some_list.size() == 2UZ);
        REQUIRE_FALSE(some_list.empty());
    }

    SECTION("Push back three elements")
    {
        forfun::experimental::container::list some_list{};

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());

        some_list.push_back(1319);

        REQUIRE(some_list.front() == 1319);
        REQUIRE(some_list.back() == 1319);
        REQUIRE(some_list.size() == 1UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.push_back(1321);

        REQUIRE(some_list.front() == 1319);
        REQUIRE(some_list.back() == 1321);
        REQUIRE(some_list.size() == 2UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.push_back(1327);

        REQUIRE(some_list.front() == 1319);
        REQUIRE(some_list.back() == 1327);
        REQUIRE(some_list.size() == 3UZ);
        REQUIRE_FALSE(some_list.empty());
    }

    SECTION("Push back four elements")
    {
        forfun::experimental::container::list some_list{};

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());

        some_list.push_back(1361);

        REQUIRE(some_list.front() == 1361);
        REQUIRE(some_list.back() == 1361);
        REQUIRE(some_list.size() == 1UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.push_back(1021);

        REQUIRE(some_list.front() == 1361);
        REQUIRE(some_list.back() == 1021);
        REQUIRE(some_list.size() == 2UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.push_back(1367);

        REQUIRE(some_list.front() == 1361);
        REQUIRE(some_list.back() == 1367);
        REQUIRE(some_list.size() == 3UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.push_back(1373);

        REQUIRE(some_list.front() == 1361);
        REQUIRE(some_list.back() == 1373);
        REQUIRE(some_list.size() == 4UZ);
        REQUIRE_FALSE(some_list.empty());
    }

    SECTION("Pop back one element out of list of one element")
    {
        forfun::experimental::container::list some_list{};
        some_list.push_back(1381);

        some_list.pop_back();

        REQUIRE(some_list.empty());

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
    }

    SECTION("Pop back one element out of list of two elements")
    {
        forfun::experimental::container::list some_list{};
        some_list.push_back(1399);
        some_list.push_back(1409);

        some_list.pop_back();

        REQUIRE_FALSE(some_list.empty());
        REQUIRE(some_list.size() == 1UZ);
        REQUIRE(some_list.front() == 1399);
        REQUIRE(some_list.back() == 1399);
    }

    SECTION("Pop back one element out of list of three elements")
    {
        forfun::experimental::container::list some_list{};
        some_list.push_back(1399);
        some_list.push_back(1409);
        some_list.push_back(1423);

        some_list.pop_back();

        REQUIRE_FALSE(some_list.empty());
        REQUIRE(some_list.size() == 2UZ);
        REQUIRE(some_list.front() == 1399);
        REQUIRE(some_list.back() == 1409);
    }

    SECTION("Clear empty list")
    {
        forfun::experimental::container::list some_list{};

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());

        some_list.clear();

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());
    }

    SECTION("Clear list of one")
    {
        forfun::experimental::container::list some_list{};
        some_list.push_back(5);

        REQUIRE(some_list.size() == 1UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.clear();

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());
    }

    SECTION("Clear list of three")
    {
        forfun::experimental::container::list some_list{};
        some_list.push_back(5);
        some_list.push_back(7);
        some_list.push_back(11);

        REQUIRE(some_list.size() == 3UZ);
        REQUIRE_FALSE(some_list.empty());

        some_list.clear();

        // NOLINTNEXTLINE(readability-container-size-empty)
        REQUIRE(some_list.size() == 0UZ);
        REQUIRE(some_list.empty());
    }

    SECTION("Method front() returns a reference")
    {
        forfun::experimental::container::list some_list{};

        REQUIRE(some_list.empty());

        some_list.push_back(1339);

        REQUIRE(some_list.front() == 1339);

        some_list.front() = 1340;

        REQUIRE(some_list.front() == 1340);
    }

    SECTION("Method front() const returns a reference to const")
    {
        forfun::experimental::container::list some_list{};

        REQUIRE(some_list.empty());

        some_list.push_back(1337);

        forfun::experimental::container::list const& alias{some_list};

        REQUIRE(alias.front() == 1337);

        some_list.front() = 1338;

        REQUIRE(alias.front() == 1338);
    }
}
