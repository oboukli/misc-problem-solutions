// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <iterator>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/list.hpp"

TEST_CASE("Linked list", "[container][list][dynamic_allocation]")
{
    SECTION("Iterator")
    {
        using forfun::container::list;

        STATIC_REQUIRE(std::bidirectional_iterator<list::iterator>);

        STATIC_REQUIRE(std::indirectly_writable<list::iterator, int>);
    }

    SECTION("Const iterator")
    {
        using forfun::container::list;

        STATIC_REQUIRE(std::bidirectional_iterator<list::const_iterator>);

        STATIC_REQUIRE_FALSE(
            std::indirectly_writable<list::const_iterator, int>
        );
    }

    SECTION("Non-const method front() returns a non-const reference")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list&>().front()),
                forfun::container::list::reference>
        );
    }

    SECTION("Method `front() const` returns a reference to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list const&>().front()),
                forfun::container::list::const_reference>
        );
    }

    SECTION("Non-const method back() returns a non-const reference")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list&>().back()),
                forfun::container::list::reference>
        );
    }

    SECTION("Method `back() const` returns a reference to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list const&>().back()),
                forfun::container::list::const_reference>
        );
    }

    SECTION("Method `begin()` returns iterator")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list>().begin()),
                forfun::container::list::iterator>
        );
    }

    SECTION("Method `begin() const` returns iterator to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list const&>().begin()),
                forfun::container::list::const_iterator>
        );
    }

    SECTION("Method `cbegin()` returns iterator to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list>().cbegin()),
                forfun::container::list::const_iterator>
        );
    }

    SECTION("Method `cbegin() const` returns iterator to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list const&>().cbegin()),
                forfun::container::list::const_iterator>
        );
    }

    SECTION("Method `end()` returns iterator")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list>().end()),
                forfun::container::list::iterator>
        );
    }

    SECTION("Method `end() const` returns iterator to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list const&>().end()),
                forfun::container::list::const_iterator>
        );
    }

    SECTION("Method `cend()` returns iterator to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list>().cend()),
                forfun::container::list::const_iterator>
        );
    }

    SECTION("Method `cend() const` returns iterator to const")
    {
        using forfun::container::list;

        STATIC_REQUIRE(
            std::same_as<
                decltype(std::declval<list const&>().cend()),
                forfun::container::list::const_iterator>
        );
    }
}
