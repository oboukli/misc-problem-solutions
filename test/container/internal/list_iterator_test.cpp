// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iterator>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/internal/list_iterator.hpp"
#include "forfun/container/internal/list_node.hpp"
#include "forfun/container/list.hpp"

TEST_CASE("Linked list iterator", "[container][list][list_iterator]")
{
    using forfun::experimental::container::list;
    using forfun::experimental::container::internal::list_iterator;
    using forfun::experimental::container::internal::list_node;

    SECTION("Default constructor")
    {
        list_iterator iterator1{};
        list_iterator iterator2{};

        REQUIRE(iterator2 == iterator1);
    }

    SECTION("Copy constructor")
    {
        list_node node{1427, nullptr, nullptr};
        list_iterator iterator1{&node};
        list_iterator iterator2{iterator1};

        REQUIRE(*iterator2 == 1427);
        REQUIRE(iterator2 == iterator1);
    }

    SECTION("Copy assignment")
    {
        list_node node1{1429, nullptr, nullptr};
        list_iterator iterator1{&node1};

        list_node node2{1433, nullptr, nullptr};
        [[maybe_unused]] list_iterator iterator2{&node2};

        iterator2 = iterator1;

        REQUIRE(*iterator2 == 1429);
        REQUIRE(iterator2 == iterator1);
    }

    SECTION("Move constructor")
    {
        list_node node{1439, nullptr, nullptr};
        list_iterator iterator1{&node};
        list_iterator iterator2{std::move(iterator1)};

        REQUIRE(*iterator2 == 1439);
        // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-invalid-access-moved)
        REQUIRE_FALSE(iterator2 == iterator1);
    }

    SECTION("Move assignment")
    {
        list_node node1{1447, nullptr, nullptr};
        list_iterator iterator1{&node1};

        list_node node2{1451, nullptr, nullptr};
        [[maybe_unused]] list_iterator iterator2{&node2};

        iterator2 = std::move(iterator1);

        REQUIRE(*iterator2 == 1447);
        // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-invalid-access-moved)
        REQUIRE_FALSE(iterator2 == iterator1);
    }

    SECTION("Iterator and sentinel of empty list are equal")
    {
        list const some_list{};

        REQUIRE(some_list.begin() == some_list.end());
        REQUIRE_FALSE(some_list.begin() != some_list.end());
    }

    SECTION("Iterator of non-empty list is not sentinel")
    {
        list some_list{};
        some_list.push_back(1009);

        REQUIRE_FALSE(some_list.begin() == some_list.end());
    }

    SECTION("Iterator and sentinel of non-empty list are unequal")
    {
        list some_list{};
        some_list.push_back(1019);

        REQUIRE(some_list.begin() != some_list.end());
    }

    SECTION("Empty list iterator equality")
    {
        list const some_list{};

        REQUIRE(some_list.begin() == some_list.begin());
        REQUIRE_FALSE(some_list.begin() != some_list.begin());
    }

    SECTION("Non-empty list iterator equality")
    {
        list some_list{};
        some_list.push_back(1049);

        REQUIRE(some_list.begin() == some_list.begin());
        REQUIRE_FALSE(some_list.begin() != some_list.begin());
    }

    SECTION("Iterator inequality")
    {
        list some_list{};
        some_list.push_back(1061);
        some_list.push_back(1063);

        auto iter{some_list.begin()};
        ++iter;

        REQUIRE(iter != some_list.begin());
        REQUIRE_FALSE(iter == some_list.begin());
    }

    SECTION("Dereferencing iterator of begin")
    {
        list some_list{};

        some_list.push_back(1283);

        REQUIRE(*some_list.begin() == 1283);
    }

    SECTION("Dereferencing iterator and mutating dereferenced element")
    {
        list some_list{};

        some_list.push_back(1291);
        REQUIRE(*some_list.begin() == 1291);

        some_list.front() = 1297;

        REQUIRE(*some_list.begin() == 1297);
    }
}

TEST_CASE("Increment linked list iterator", "[container][list][list_iterator]")
{
    using forfun::experimental::container::list;

    SECTION("Increment iterator once")
    {
        list some_list{};

        some_list.push_back(1091);
        some_list.push_back(1093);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        ++iter;

        REQUIRE(*iter == 1093);
    }

    SECTION("Increment iterator an even number of times within range")
    {
        list some_list{};

        some_list.push_back(1109);
        some_list.push_back(1117);
        some_list.push_back(1123);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        ++iter;
        ++iter;

        REQUIRE(*iter == 1123);
    }

    SECTION("Increment iterator an odd number of times within range")
    {
        list some_list{};

        some_list.push_back(1163);
        some_list.push_back(1171);
        some_list.push_back(1181);
        some_list.push_back(1187);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(*iter == 1187);
    }

    SECTION("Increment iterator one time off size")
    {
        list some_list{};

        some_list.push_back(1223);
        some_list.push_back(1229);
        some_list.push_back(1231);
        some_list.push_back(1237);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        ++iter;
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(iter == some_list.end());
    }

    SECTION("Postfix increment iterator once")
    {
        list some_list{};

        some_list.push_back(1453);
        some_list.push_back(1459);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        iter++;

        REQUIRE(*iter == 1459);
    }

    SECTION("Postfix increment iterator an even number of times within range")
    {
        list some_list{};

        some_list.push_back(1471);
        some_list.push_back(1481);
        some_list.push_back(1483);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        iter++;
        iter++;

        REQUIRE(*iter == 1483);
    }

    SECTION("Postfix increment iterator an odd number of times within range")
    {
        list some_list{};

        some_list.push_back(1487);
        some_list.push_back(1489);
        some_list.push_back(1493);
        some_list.push_back(1499);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        iter++;
        iter++;
        iter++;

        REQUIRE(*iter == 1499);
    }

    SECTION("Postfix increment iterator one time off size")
    {
        list some_list{};

        some_list.push_back(1511);
        some_list.push_back(1523);
        some_list.push_back(1531);
        some_list.push_back(1543);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        iter++;
        iter++;
        iter++;
        iter++;

        REQUIRE(iter == some_list.end());
    }

    SECTION("Result of postfix increment")
    {
        list some_list{};

        some_list.push_back(1549);
        some_list.push_back(1553);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();

        REQUIRE(iter++ == some_list.begin());
        REQUIRE_FALSE(iter == some_list.begin());
        REQUIRE(*iter == 1553);
    }

    SECTION("Dereferencing result of postfix increment")
    {
        list some_list{};

        some_list.push_back(1559);
        some_list.push_back(1567);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();

        REQUIRE(*iter == 1559);
        REQUIRE(*iter++ == 1559);
        REQUIRE(*iter == 1567);
    }
}

TEST_CASE("Decrement linked list iterator", "[container][list][list_iterator]")
{
    using forfun::experimental::container::list;

    SECTION("Decrement iterator once from end")
    {
        list some_list{};

        some_list.push_back(1579);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        --iter;

        REQUIRE(*iter == 1579);
    }

    SECTION("Decrement iterator an even number of times within range")
    {
        list some_list{};

        some_list.push_back(1597);
        some_list.push_back(1601);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        --iter;
        --iter;

        REQUIRE(*iter == 1597);
    }

    SECTION("Decrement iterator an odd number of times within range")
    {
        list some_list{};

        some_list.push_back(1607);
        some_list.push_back(1609);
        some_list.push_back(1613);
        some_list.push_back(1619);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        --iter;
        --iter;
        --iter;

        REQUIRE(*iter == 1609);
    }

    SECTION("Decrement iterator to beginning iterator")
    {
        list some_list{};

        some_list.push_back(1621);
        some_list.push_back(1627);
        some_list.push_back(1637);
        some_list.push_back(1657);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        --iter;
        --iter;
        --iter;
        --iter;

        REQUIRE(iter == some_list.begin());
    }

    SECTION("Postfix decrement iterator once")
    {
        list some_list{};

        some_list.push_back(1663);
        some_list.push_back(1667);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        iter--;

        REQUIRE(*iter == 1667);
    }

    SECTION("Postfix decrement iterator an even number of times within range")
    {
        list some_list{};

        some_list.push_back(1669);
        some_list.push_back(1693);
        some_list.push_back(1697);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        iter--;
        iter--;

        REQUIRE(*iter == 1693);
    }

    SECTION("Postfix decrement iterator an odd number of times within range")
    {
        list some_list{};

        some_list.push_back(1699);
        some_list.push_back(1709);
        some_list.push_back(1721);
        some_list.push_back(1723);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        iter--;
        iter--;
        iter--;

        REQUIRE(*iter == 1709);
    }

    SECTION("Postfix decrement iterator one time off size")
    {
        list some_list{};

        some_list.push_back(1733);
        some_list.push_back(1741);
        some_list.push_back(1747);
        some_list.push_back(1753);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        iter--;
        iter--;
        iter--;
        iter--;

        REQUIRE(iter == some_list.begin());
    }

    SECTION("Result of postfix decrement")
    {
        list some_list{};

        some_list.push_back(1759);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();

        REQUIRE(iter-- == some_list.end());
        REQUIRE_FALSE(iter == some_list.end());
        REQUIRE(iter == some_list.begin());
    }

    SECTION("Dereferencing result of postfix decrement")
    {
        list some_list{};

        some_list.push_back(1783);
        some_list.push_back(1787);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();
        --iter;

        REQUIRE(*iter-- == 1787);
    }
}

TEST_CASE("Linked list iterator sentinel", "[container][list][list_iterator]")
{
    using forfun::experimental::container::list;

    SECTION("Iterator at beginning of empty list")
    {
        list const some_list{};

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();

        REQUIRE(iter == std::default_sentinel);
        REQUIRE_FALSE(iter != std::default_sentinel);
    }

    SECTION("Iterator at beginning of non-empty list")
    {
        list some_list{};

        some_list.push_back(1571);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();

        REQUIRE_FALSE(iter == std::default_sentinel);
        REQUIRE(iter != std::default_sentinel);
    }

    SECTION("Iterator at end of list")
    {
        list const some_list{};

        forfun::experimental::container::internal::list_iterator iter
            = some_list.end();

        REQUIRE(iter == std::default_sentinel);
        REQUIRE_FALSE(iter != std::default_sentinel);
    }

    SECTION("Incremented iterator to end of non-empty list")
    {
        list some_list{};

        some_list.push_back(1583);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        ++iter;

        REQUIRE(iter == std::default_sentinel);
        REQUIRE_FALSE(iter != std::default_sentinel);
    }

    SECTION("Incremented iterator to non-end of non-empty list")
    {
        list some_list{};

        some_list.push_back(1789);
        some_list.push_back(1801);

        forfun::experimental::container::internal::list_iterator iter
            = some_list.begin();
        ++iter;

        REQUIRE_FALSE(iter == std::default_sentinel);
        REQUIRE(iter != std::default_sentinel);
    }
}
