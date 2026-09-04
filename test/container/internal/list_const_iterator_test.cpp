// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <tuple>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/internal/list_const_iterator.hpp"
#include "forfun/container/internal/list_node.hpp"
#include "forfun/container/list.hpp"

TEST_CASE(
    "Linked list const iterator", "[container][list][list_const_iterator]"
)
{
    using forfun::container::internal::list_const_iterator;
    using forfun::container::internal::list_node;

    SECTION("Default constructor (case 1)")
    {
        list_const_iterator iterator1;
        list_const_iterator iterator2;

        REQUIRE(iterator1 == iterator2);
    }

    SECTION("Default constructor (case 2)")
    {
        list_const_iterator iterator1{};
        list_const_iterator iterator2{};

        REQUIRE(iterator1 == iterator2);
    }

    SECTION("Copy constructor")
    {
        list_node node{1811, nullptr, nullptr};
        list_const_iterator iterator1{&node};

        list_const_iterator iterator2(iterator1);

        CHECK(iterator1 == iterator2);
        REQUIRE(*iterator2 == 1811);
    }

    SECTION("Move constructor")
    {
        list_node node{1847, nullptr, nullptr};

        list_const_iterator const iterator1(list_const_iterator{&node});

        REQUIRE(*iterator1 == 1847);
    }

    SECTION("Copy assignment")
    {
        list_node node1{1823, nullptr, nullptr};
        list_const_iterator iterator1{&node1};
        list_const_iterator iterator2;

        iterator2 = iterator1;

        CHECK(iterator2 == iterator1);
        REQUIRE(*iterator2 == 1823);
    }

    SECTION("Copy assignment to self")
    {
        list_node node1{2381, nullptr, nullptr};
        list_const_iterator iterator1{&node1};
        list_const_iterator const& alias{iterator1};

        iterator1 = alias;

        CHECK(*alias == 2381);
        CHECK(iterator1 == alias);
        REQUIRE(*iterator1 == 2381);
    }

    SECTION("Move assignment")
    {
        list_node node1{1861, nullptr, nullptr};
        list_const_iterator iterator2;

        iterator2 = list_const_iterator{&node1};

        REQUIRE(*iterator2 == 1861);
    }

    SECTION("Move assignment to self")
    {
        list_node node1{2383, nullptr, nullptr};
        list_const_iterator iterator1{&node1};
        list_const_iterator& alias{iterator1};

        // NOLINTNEXTLINE(performance-move-const-arg)
        iterator1 = std::move(alias);

        REQUIRE(*iterator1 == 2383);
    }

    SECTION("Const iterator and const sentinel of empty list are equal")
    {
        forfun::container::list const some_list{};

        REQUIRE(some_list.cbegin() == some_list.cend());
        REQUIRE_FALSE(some_list.cbegin() != some_list.cend());
    }

    SECTION("Const iterator of non-empty list is not const sentinel")
    {
        forfun::container::list some_list{};
        some_list.push_back(1871);

        REQUIRE_FALSE(some_list.cbegin() == some_list.cend());
    }

    SECTION("Const iterator and const sentinel of non-empty list are unequal")
    {
        forfun::container::list some_list{};
        some_list.push_back(1873);

        REQUIRE(some_list.cbegin() != some_list.cend());
    }

    SECTION("Empty list const iterator equality")
    {
        forfun::container::list const some_list{};

        REQUIRE(some_list.cbegin() == some_list.cbegin());
        REQUIRE_FALSE(some_list.cbegin() != some_list.cbegin());
    }

    SECTION("Non-empty list const iterator equality")
    {
        forfun::container::list some_list{};
        some_list.push_back(1877);

        REQUIRE(some_list.cbegin() == some_list.cbegin());
        REQUIRE_FALSE(some_list.cbegin() != some_list.cbegin());
    }

    SECTION("Const iterator inequality")
    {
        forfun::container::list some_list{};
        some_list.push_back(1879);
        some_list.push_back(1889);

        auto iter{some_list.cbegin()};
        ++iter;

        REQUIRE(iter != some_list.cbegin());
        REQUIRE_FALSE(iter == some_list.cbegin());
    }

    SECTION("Dereferencing const iterator of cbegin")
    {
        forfun::container::list some_list{};

        some_list.push_back(1901);

        REQUIRE(*some_list.cbegin() == 1901);
    }
}

TEST_CASE(
    "Increment linked list const iterator",
    "[container][list][list_const_iterator]"
)
{
    SECTION("Increment const iterator once")
    {
        forfun::container::list some_list{};

        some_list.push_back(1907);
        some_list.push_back(1913);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        ++iter;

        REQUIRE(*iter == 1913);
    }

    SECTION("Increment const iterator an even number of times within range")
    {
        forfun::container::list some_list{};

        some_list.push_back(1931);
        some_list.push_back(1933);
        some_list.push_back(1949);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        ++iter;
        ++iter;

        REQUIRE(*iter == 1949);
    }

    SECTION("Increment const iterator an odd number of times within range")
    {
        forfun::container::list some_list{};

        some_list.push_back(1951);
        some_list.push_back(1973);
        some_list.push_back(1979);
        some_list.push_back(1987);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(*iter == 1987);
    }

    SECTION("Increment const iterator one time off size")
    {
        forfun::container::list some_list{};

        some_list.push_back(1993);
        some_list.push_back(1997);
        some_list.push_back(1999);
        some_list.push_back(2003);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        ++iter;
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(iter == some_list.cend());
    }

    SECTION("Postfix increment const iterator once")
    {
        forfun::container::list some_list{};

        some_list.push_back(2011);
        some_list.push_back(2017);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        std::ignore = iter++;

        REQUIRE(*iter == 2017);
    }

    SECTION(
        "Postfix increment const iterator an even number of times within range"
    )
    {
        forfun::container::list some_list{};

        some_list.push_back(2027);
        some_list.push_back(2029);
        some_list.push_back(2039);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        auto tmp{iter++};
        tmp = iter++;

        REQUIRE(*iter == 2039);
    }

    SECTION(
        "Postfix increment const iterator an odd number of times within range"
    )
    {
        forfun::container::list some_list{};

        some_list.push_back(2053);
        some_list.push_back(2063);
        some_list.push_back(2069);
        some_list.push_back(2081);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        auto tmp{iter++};
        tmp = iter++;
        tmp = iter++;

        REQUIRE(*iter == 2081);
    }

    SECTION("Postfix increment const iterator one time off size")
    {
        forfun::container::list some_list{};

        some_list.push_back(2083);
        some_list.push_back(2087);
        some_list.push_back(2089);
        some_list.push_back(2099);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };
        auto tmp{iter++};
        tmp = iter++;
        tmp = iter++;
        tmp = iter++;

        REQUIRE(iter == some_list.cend());
    }

    SECTION("Result of postfix increment")
    {
        forfun::container::list some_list{};

        some_list.push_back(2111);
        some_list.push_back(2113);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };

        REQUIRE(iter++ == some_list.cbegin());
        REQUIRE_FALSE(iter == some_list.cbegin());
        REQUIRE(*iter == 2113);
    }

    SECTION("Dereferencing result of postfix increment")
    {
        forfun::container::list some_list{};

        some_list.push_back(2129);
        some_list.push_back(2131);

        forfun::container::internal::list_const_iterator iter{
            some_list.cbegin()
        };

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
        forfun::container::list some_list{};

        some_list.push_back(2137);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        --iter;

        REQUIRE(*iter == 2137);
    }

    SECTION("Decrement const iterator an even number of times within range")
    {
        forfun::container::list some_list{};

        some_list.push_back(2141);
        some_list.push_back(2143);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        --iter;
        --iter;

        REQUIRE(*iter == 2141);
    }

    SECTION("Decrement const iterator an odd number of times within range")
    {
        forfun::container::list some_list{};

        some_list.push_back(2153);
        some_list.push_back(2161);
        some_list.push_back(2179);
        some_list.push_back(2203);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        --iter;
        --iter;
        --iter;

        REQUIRE(*iter == 2161);
    }

    SECTION("Decrement const iterator to beginning const iterator")
    {
        forfun::container::list some_list{};

        some_list.push_back(2207);
        some_list.push_back(2213);
        some_list.push_back(2221);
        some_list.push_back(2237);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        --iter;
        --iter;
        --iter;
        --iter;

        REQUIRE(iter == some_list.cbegin());
    }

    SECTION("Postfix decrement const iterator once")
    {
        forfun::container::list some_list{};

        some_list.push_back(2239);
        some_list.push_back(2243);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        std::ignore = iter--;

        REQUIRE(*iter == 2243);
    }

    SECTION(
        "Postfix decrement const iterator an even number of times within range"
    )
    {
        forfun::container::list some_list{};

        some_list.push_back(2251);
        some_list.push_back(2267);
        some_list.push_back(2269);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        auto tmp{iter--};
        tmp = iter--;

        REQUIRE(*iter == 2267);
    }

    SECTION(
        "Postfix decrement const iterator an odd number of times within range"
    )
    {
        forfun::container::list some_list{};

        some_list.push_back(2273);
        some_list.push_back(2281);
        some_list.push_back(2287);
        some_list.push_back(2293);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        auto tmp{iter--};
        tmp = iter--;
        tmp = iter--;

        REQUIRE(*iter == 2281);
    }

    SECTION("Postfix decrement const iterator one time off size")
    {
        forfun::container::list some_list{};

        some_list.push_back(2297);
        some_list.push_back(2309);
        some_list.push_back(2311);
        some_list.push_back(2333);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        auto tmp{iter--};
        tmp = iter--;
        tmp = iter--;
        tmp = iter--;

        REQUIRE(iter == some_list.cbegin());
    }

    SECTION("Result of postfix decrement")
    {
        forfun::container::list some_list{};

        some_list.push_back(2377);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();

        REQUIRE(iter-- == some_list.cend());
        REQUIRE_FALSE(iter == some_list.cend());
        REQUIRE(iter == some_list.cbegin());
    }

    SECTION("Dereferencing result of postfix decrement")
    {
        forfun::container::list some_list{};

        some_list.push_back(2339);
        some_list.push_back(2341);

        forfun::container::internal::list_const_iterator iter
            = some_list.cend();
        --iter;

        REQUIRE(*iter-- == 2341);
    }
}
