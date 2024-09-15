// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
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

        // clang-format off
        STATIC_REQUIRE_FALSE(
            std::indirectly_writable<list::const_iterator, int>
        );
        // clang-format on
    }

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

    SECTION("Pop back one element out of empty list")
    {
        forfun::experimental::container::list list{};

        list.pop_back();

        REQUIRE(list.empty());
        REQUIRE(list.size() == std::size_t{0U});
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
}
