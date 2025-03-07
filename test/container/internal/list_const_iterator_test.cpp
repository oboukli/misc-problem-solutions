// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <iterator>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/internal/list_const_iterator.hpp"
#include "forfun/container/internal/list_node.hpp"
#include "forfun/container/list.hpp"

TEST_CASE(
    "Linked list const iterator", "[container][list][list_const_iterator]"
)
{
    using forfun::experimental::container::list;
    using forfun::experimental::container::internal::list_const_iterator;
    using forfun::experimental::container::internal::list_node;

    SECTION("Default constructor")
    {
        list_const_iterator iterator1{};
        list_const_iterator iterator2{};

        REQUIRE(iterator2 == iterator1);
    }

    SECTION("Copy constructor")
    {
        list_node node{1811, nullptr, nullptr};
        list_const_iterator iterator1{&node};
        list_const_iterator iterator2{iterator1};

        REQUIRE(*iterator2 == 1811);
        REQUIRE(iterator2 == iterator1);
    }

    SECTION("Copy assignment")
    {
        list_node node1{1823, nullptr, nullptr};
        list_const_iterator iterator1{&node1};

        list_node node2{1831, nullptr, nullptr};
        list_const_iterator iterator2{&node2};

        iterator2 = iterator1;

        REQUIRE(*iterator2 == 1823);
        REQUIRE(iterator2 == iterator1);
    }

    SECTION("Move constructor")
    {
        list_node node{1847, nullptr, nullptr};
        list_const_iterator iterator1{&node};
        list_const_iterator iterator2{std::move(iterator1)};

        REQUIRE(*iterator2 == 1847);
        // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-invalid-access-moved)
        REQUIRE_FALSE(iterator2 == iterator1);
    }

    SECTION("Move assignment")
    {
        list_node node1{1861, nullptr, nullptr};
        list_const_iterator iterator1{&node1};

        list_node node2{1867, nullptr, nullptr};
        list_const_iterator iterator2{&node2};

        iterator2 = std::move(iterator1);

        REQUIRE(*iterator2 == 1861);
        // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-invalid-access-moved)
        REQUIRE_FALSE(iterator2 == iterator1);
    }

    SECTION("Const iterator and const sentinel of empty list are equal")
    {
        forfun::experimental::container::list const list{};

        REQUIRE(list.cbegin() == list.cend());
        REQUIRE_FALSE(list.cbegin() != list.cend());
    }

    SECTION("Const iterator of non-empty list is not const sentinel")
    {
        forfun::experimental::container::list list{};
        list.push_back(1871);

        REQUIRE_FALSE(list.cbegin() == list.cend());
    }

    SECTION("Const iterator and const sentinel of non-empty list are unequal")
    {
        forfun::experimental::container::list list{};
        list.push_back(1873);

        REQUIRE(list.cbegin() != list.cend());
    }

    SECTION("Empty list const iterator equality")
    {
        forfun::experimental::container::list const list{};

        REQUIRE(list.cbegin() == list.cbegin());
        REQUIRE_FALSE(list.cbegin() != list.cbegin());
    }

    SECTION("Non-empty list const iterator equality")
    {
        forfun::experimental::container::list list{};
        list.push_back(1877);

        REQUIRE(list.cbegin() == list.cbegin());
        REQUIRE_FALSE(list.cbegin() != list.cbegin());
    }

    SECTION("Const iterator inequality")
    {
        forfun::experimental::container::list list{};
        list.push_back(1879);
        list.push_back(1889);

        auto iter{list.cbegin()};
        ++iter;

        REQUIRE(iter != list.cbegin());
        REQUIRE_FALSE(iter == list.cbegin());
    }

    SECTION("Dereferencing const iterator of cbegin")
    {
        forfun::experimental::container::list list{};

        list.push_back(1901);

        REQUIRE(*list.cbegin() == 1901);
    }
}

TEST_CASE(
    "Increment linked list const iterator",
    "[container][list][list_const_iterator]"
)
{
    SECTION("Increment const iterator once")
    {
        forfun::experimental::container::list list{};

        list.push_back(1907);
        list.push_back(1913);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        ++iter;

        REQUIRE(*iter == 1913);
    }

    SECTION("Increment const iterator an even number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(1931);
        list.push_back(1933);
        list.push_back(1949);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        ++iter;
        ++iter;

        REQUIRE(*iter == 1949);
    }

    SECTION("Increment const iterator an odd number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(1951);
        list.push_back(1973);
        list.push_back(1979);
        list.push_back(1987);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(*iter == 1987);
    }

    SECTION("Increment const iterator one time off size")
    {
        forfun::experimental::container::list list{};

        list.push_back(1993);
        list.push_back(1997);
        list.push_back(1999);
        list.push_back(2003);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        ++iter;
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(iter == list.cend());
    }

    SECTION("Postfix increment const iterator once")
    {
        forfun::experimental::container::list list{};

        list.push_back(2011);
        list.push_back(2017);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        iter++;

        REQUIRE(*iter == 2017);
    }

    SECTION(
        "Postfix increment const iterator an even number of times within range"
    )
    {
        forfun::experimental::container::list list{};

        list.push_back(2027);
        list.push_back(2029);
        list.push_back(2039);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        iter++;
        iter++;

        REQUIRE(*iter == 2039);
    }

    SECTION(
        "Postfix increment const iterator an odd number of times within range"
    )
    {
        forfun::experimental::container::list list{};

        list.push_back(2053);
        list.push_back(2063);
        list.push_back(2069);
        list.push_back(2081);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        iter++;
        iter++;
        iter++;

        REQUIRE(*iter == 2081);
    }

    SECTION("Postfix increment const iterator one time off size")
    {
        forfun::experimental::container::list list{};

        list.push_back(2083);
        list.push_back(2087);
        list.push_back(2089);
        list.push_back(2099);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        iter++;
        iter++;
        iter++;
        iter++;

        REQUIRE(iter == list.cend());
    }

    SECTION("Result of postfix increment")
    {
        forfun::experimental::container::list list{};

        list.push_back(2111);
        list.push_back(2113);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();

        REQUIRE(iter++ == list.cbegin());
        REQUIRE_FALSE(iter == list.cbegin());
        REQUIRE(*iter == 2113);
    }

    SECTION("Dereferencing result of postfix increment")
    {
        forfun::experimental::container::list list{};

        list.push_back(2129);
        list.push_back(2131);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();

        REQUIRE(*iter == 2129);
        REQUIRE(*iter++ == 2129);
        REQUIRE(*iter == 2131);
    }
}

TEST_CASE(
    "Decrement linked list const iterator",
    "[container][list][list_const_iterator]"
)
{
    SECTION("Decrement const iterator once from end")
    {
        forfun::experimental::container::list list{};

        list.push_back(2137);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        --iter;

        REQUIRE(*iter == 2137);
    }

    SECTION("Decrement const iterator an even number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(2141);
        list.push_back(2143);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        --iter;
        --iter;

        REQUIRE(*iter == 2141);
    }

    SECTION("Decrement const iterator an odd number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(2153);
        list.push_back(2161);
        list.push_back(2179);
        list.push_back(2203);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        --iter;
        --iter;
        --iter;

        REQUIRE(*iter == 2161);
    }

    SECTION("Decrement const iterator to beginning const iterator")
    {
        forfun::experimental::container::list list{};

        list.push_back(2207);
        list.push_back(2213);
        list.push_back(2221);
        list.push_back(2237);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        --iter;
        --iter;
        --iter;
        --iter;

        REQUIRE(iter == list.cbegin());
    }

    SECTION("Postfix decrement const iterator once")
    {
        forfun::experimental::container::list list{};

        list.push_back(2239);
        list.push_back(2243);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        iter--;

        REQUIRE(*iter == 2243);
    }

    SECTION(
        "Postfix decrement const iterator an even number of times within range"
    )
    {
        forfun::experimental::container::list list{};

        list.push_back(2251);
        list.push_back(2267);
        list.push_back(2269);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        iter--;
        iter--;

        REQUIRE(*iter == 2267);
    }

    SECTION(
        "Postfix decrement const iterator an odd number of times within range"
    )
    {
        forfun::experimental::container::list list{};

        list.push_back(2273);
        list.push_back(2281);
        list.push_back(2287);
        list.push_back(2293);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        iter--;
        iter--;
        iter--;

        REQUIRE(*iter == 2281);
    }

    SECTION("Postfix decrement const iterator one time off size")
    {
        forfun::experimental::container::list list{};

        list.push_back(2297);
        list.push_back(2309);
        list.push_back(2311);
        list.push_back(2333);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        iter--;
        iter--;
        iter--;
        iter--;

        REQUIRE(iter == list.cbegin());
    }

    SECTION("Result of postfix decrement")
    {
        forfun::experimental::container::list list{};

        list.push_back(2377);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();

        REQUIRE(iter-- == list.cend());
        REQUIRE_FALSE(iter == list.cend());
        REQUIRE(iter == list.cbegin());
    }

    SECTION("Dereferencing result of postfix decrement")
    {
        forfun::experimental::container::list list{};

        list.push_back(2339);
        list.push_back(2341);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();
        --iter;

        REQUIRE(*iter-- == 2341);
    }
}

TEST_CASE(
    "Linked list const iterator sentinel",
    "[container][list][list_const_iterator]"
)
{
    SECTION("Iterator at beginning of empty list")
    {
        forfun::experimental::container::list const list{};

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();

        REQUIRE(iter == std::default_sentinel);
        REQUIRE_FALSE(iter != std::default_sentinel);
    }

    SECTION("Iterator at beginning of non-empty list")
    {
        forfun::experimental::container::list list{};

        list.push_back(2347);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();

        REQUIRE_FALSE(iter == std::default_sentinel);
        REQUIRE(iter != std::default_sentinel);
    }

    SECTION("Iterator at end of list")
    {
        forfun::experimental::container::list const list{};

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cend();

        REQUIRE(iter == std::default_sentinel);
        REQUIRE_FALSE(iter != std::default_sentinel);
    }

    SECTION("Incremented const iterator to end of non-empty list")
    {
        forfun::experimental::container::list list{};

        list.push_back(2351);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        ++iter;

        REQUIRE(iter == std::default_sentinel);
        REQUIRE_FALSE(iter != std::default_sentinel);
    }

    SECTION("Incremented const iterator to non-end of non-empty list")
    {
        forfun::experimental::container::list list{};

        list.push_back(2357);
        list.push_back(2371);

        forfun::experimental::container::internal::list_const_iterator iter
            = list.cbegin();
        ++iter;

        REQUIRE_FALSE(iter == std::default_sentinel);
        REQUIRE(iter != std::default_sentinel);
    }
}
