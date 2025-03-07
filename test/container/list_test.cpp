// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/list.hpp"

TEST_CASE("Linked list", "[container][list][dynamic_allocation]")
{
    SECTION("List is initially empty")
    {
        forfun::experimental::container::list const list{};

        REQUIRE(list.empty());
    }

    SECTION("List's initial size is zero")
    {
        forfun::experimental::container::list const list{};

        REQUIRE(list.size() == std::size_t{0U});
    }

    SECTION("Push back one element (benchmark case)")
    {
        forfun::experimental::container::list list{};

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());

        list.push_back(1301);

        REQUIRE(list.front() == 1301);
        REQUIRE(list.back() == 1301);
        REQUIRE(list.size() == std::size_t{1U});
        REQUIRE_FALSE(list.empty());
    }

    SECTION("Push back two elements")
    {
        forfun::experimental::container::list list{};

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());

        list.push_back(1303);

        REQUIRE(list.front() == 1303);
        REQUIRE(list.back() == 1303);
        REQUIRE(list.size() == std::size_t{1U});
        REQUIRE_FALSE(list.empty());

        list.push_back(1307);

        REQUIRE(list.front() == 1303);
        REQUIRE(list.back() == 1307);
        REQUIRE(list.size() == std::size_t{2U});
        REQUIRE_FALSE(list.empty());
    }

    SECTION("Push back three elements")
    {
        forfun::experimental::container::list list{};

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());

        list.push_back(1319);

        REQUIRE(list.front() == 1319);
        REQUIRE(list.back() == 1319);
        REQUIRE(list.size() == std::size_t{1U});
        REQUIRE_FALSE(list.empty());

        list.push_back(1321);

        REQUIRE(list.front() == 1319);
        REQUIRE(list.back() == 1321);
        REQUIRE(list.size() == std::size_t{2U});
        REQUIRE_FALSE(list.empty());

        list.push_back(1327);

        REQUIRE(list.front() == 1319);
        REQUIRE(list.back() == 1327);
        REQUIRE(list.size() == std::size_t{3U});
        REQUIRE_FALSE(list.empty());
    }

    SECTION("Push back four elements")
    {
        forfun::experimental::container::list list{};

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());

        list.push_back(1361);

        REQUIRE(list.front() == 1361);
        REQUIRE(list.back() == 1361);
        REQUIRE(list.size() == std::size_t{1U});
        REQUIRE_FALSE(list.empty());

        list.push_back(1021);

        REQUIRE(list.front() == 1361);
        REQUIRE(list.back() == 1021);
        REQUIRE(list.size() == std::size_t{2U});
        REQUIRE_FALSE(list.empty());

        list.push_back(1367);

        REQUIRE(list.front() == 1361);
        REQUIRE(list.back() == 1367);
        REQUIRE(list.size() == std::size_t{3U});
        REQUIRE_FALSE(list.empty());

        list.push_back(1373);

        REQUIRE(list.front() == 1361);
        REQUIRE(list.back() == 1373);
        REQUIRE(list.size() == std::size_t{4U});
        REQUIRE_FALSE(list.empty());
    }

    SECTION("Pop back one element out of list of one element")
    {
        forfun::experimental::container::list list{};
        list.push_back(1381);

        list.pop_back();

        REQUIRE(list.empty());
        REQUIRE(list.size() == std::size_t{0U});
    }

    SECTION("Pop back one element out of list of two elements")
    {
        forfun::experimental::container::list list{};
        list.push_back(1399);
        list.push_back(1409);

        list.pop_back();

        REQUIRE_FALSE(list.empty());
        REQUIRE(list.size() == std::size_t{1U});
        REQUIRE(list.front() == 1399);
        REQUIRE(list.back() == 1399);
    }

    SECTION("Pop back one element out of list of three elements")
    {
        forfun::experimental::container::list list{};
        list.push_back(1399);
        list.push_back(1409);
        list.push_back(1423);

        list.pop_back();

        REQUIRE_FALSE(list.empty());
        REQUIRE(list.size() == std::size_t{2U});
        REQUIRE(list.front() == 1399);
        REQUIRE(list.back() == 1409);
    }

    SECTION("Clear empty list")
    {
        forfun::experimental::container::list list{};

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());

        list.clear();

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());
    }

    SECTION("Clear list of one")
    {
        forfun::experimental::container::list list{};
        list.push_back(5);

        REQUIRE(list.size() == std::size_t{1U});
        REQUIRE_FALSE(list.empty());

        list.clear();

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());
    }

    SECTION("Clear list of three")
    {
        forfun::experimental::container::list list{};
        list.push_back(5);
        list.push_back(7);
        list.push_back(11);

        REQUIRE(list.size() == std::size_t{3U});
        REQUIRE_FALSE(list.empty());

        list.clear();

        REQUIRE(list.size() == std::size_t{0U});
        REQUIRE(list.empty());
    }

    SECTION("Method front() returns a reference")
    {
        forfun::experimental::container::list list{};

        REQUIRE(list.empty());

        list.push_back(1339);

        REQUIRE(list.front() == 1339);

        list.front() = 1340;

        REQUIRE(list.front() == 1340);
    }

    SECTION("Method front() const returns a reference to const")
    {
        forfun::experimental::container::list list{};

        REQUIRE(list.empty());

        list.push_back(1337);

        forfun::experimental::container::list const& alias{list};

        REQUIRE(alias.front() == 1337);

        list.front() = 1338;

        REQUIRE(alias.front() == 1338);
    }
}
