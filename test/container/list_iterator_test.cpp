// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <iterator>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/internal/list_node.hpp"
#include "forfun/container/list.hpp"
#include "forfun/container/list_iterator.hpp"

TEST_CASE("Linked list iterator traits", "[linked_list][list_iterator][static]")
{
    SECTION("Iterator traits")
    {
        using iterator = forfun::experimental::container::list::iterator;
        using list_iterator = forfun::experimental::container::list_iterator;

        // clang-format off
        STATIC_REQUIRE(std::same_as<list_iterator, iterator>);

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<iterator>::iterator_category,
                std::forward_iterator_tag
            >
        );
        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<iterator>::pointer,
                forfun::experimental::container::list_node*
            >
        );

        STATIC_REQUIRE(std::same_as<std::iter_reference_t<iterator>, int&>);
        STATIC_REQUIRE(
            std::same_as<std::iter_rvalue_reference_t<iterator>, int&&>
        );
        STATIC_REQUIRE(
            std::same_as<std::iter_common_reference_t<iterator>, int&>
        );
        STATIC_REQUIRE(std::same_as<std::iter_value_t<iterator>, int>);
        // clang-format on
    }
}

TEST_CASE("Linked list iterator", "[linked_list][list_iterator]")
{
    using forfun::experimental::container::list;
    using forfun::experimental::container::list_iterator;
    using forfun::experimental::container::list_node;

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
        list_iterator iterator2{&node2};

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
        list_iterator iterator2{&node2};

        iterator2 = std::move(iterator1);

        REQUIRE(*iterator2 == 1447);
        // NOLINTNEXTLINE(bugprone-use-after-move,hicpp-invalid-access-moved)
        REQUIRE_FALSE(iterator2 == iterator1);
    }

    SECTION("Iterator and sentinel of empty list are equal")
    {
        forfun::experimental::container::list const list{};

        REQUIRE(list.begin() == list.end());
        REQUIRE_FALSE(list.begin() != list.end());
    }

    SECTION("Iterator of non-empty list is not sentinel")
    {
        forfun::experimental::container::list list{};
        list.push_back(1009);

        REQUIRE_FALSE(list.begin() == list.end());
    }

    SECTION("Iterator and sentinel of non-empty list are unequal")
    {
        forfun::experimental::container::list list{};
        list.push_back(1019);

        REQUIRE(list.begin() != list.end());
    }

    SECTION("Empty list iterator equality")
    {
        forfun::experimental::container::list const list{};

        REQUIRE(list.begin() == list.begin());
        REQUIRE_FALSE(list.begin() != list.begin());
    }

    SECTION("Non-empty list iterator equality")
    {
        forfun::experimental::container::list list{};
        list.push_back(1049);

        REQUIRE(list.begin() == list.begin());
        REQUIRE_FALSE(list.begin() != list.begin());
    }

    SECTION("Iterator inequality")
    {
        forfun::experimental::container::list list{};
        list.push_back(1061);
        list.push_back(1063);

        auto iter{list.begin()};
        ++iter;

        REQUIRE(iter != list.begin());
        REQUIRE_FALSE(iter == list.begin());
    }

    SECTION("Incrementing iterator once")
    {
        forfun::experimental::container::list list{};

        list.push_back(1091);
        list.push_back(1093);

        forfun::experimental::container::list::iterator iter = list.begin();
        ++iter;

        REQUIRE(*iter == 1093);
    }

    SECTION("Incrementing iterator an even number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(1109);
        list.push_back(1117);
        list.push_back(1123);

        forfun::experimental::container::list::iterator iter = list.begin();
        ++iter;
        ++iter;

        REQUIRE(*iter == 1123);
    }

    SECTION("Incrementing iterator an odd number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(1163);
        list.push_back(1171);
        list.push_back(1181);
        list.push_back(1187);

        forfun::experimental::container::list::iterator iter = list.begin();
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(*iter == 1187);
    }

    SECTION("Incrementing iterator one time off size")
    {
        forfun::experimental::container::list list{};

        list.push_back(1223);
        list.push_back(1229);
        list.push_back(1231);
        list.push_back(1237);

        forfun::experimental::container::list::iterator iter = list.begin();
        ++iter;
        ++iter;
        ++iter;
        ++iter;

        REQUIRE(iter == list.end());
    }

    SECTION("Post incrementing iterator once")
    {
        forfun::experimental::container::list list{};

        list.push_back(1453);
        list.push_back(1459);

        forfun::experimental::container::list::iterator iter = list.begin();
        iter++;

        REQUIRE(*iter == 1459);
    }

    SECTION("Post incrementing iterator an even number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(1471);
        list.push_back(1481);
        list.push_back(1483);

        forfun::experimental::container::list::iterator iter = list.begin();
        iter++;
        iter++;

        REQUIRE(*iter == 1483);
    }

    SECTION("Post incrementing iterator an odd number of times within range")
    {
        forfun::experimental::container::list list{};

        list.push_back(1487);
        list.push_back(1489);
        list.push_back(1493);
        list.push_back(1499);

        forfun::experimental::container::list::iterator iter = list.begin();
        iter++;
        iter++;
        iter++;

        REQUIRE(*iter == 1499);
    }

    SECTION("Post incrementing iterator one time off size")
    {
        forfun::experimental::container::list list{};

        list.push_back(1511);
        list.push_back(1523);
        list.push_back(1531);
        list.push_back(1543);

        forfun::experimental::container::list::iterator iter = list.begin();
        iter++;
        iter++;
        iter++;
        iter++;

        REQUIRE(iter == list.end());
    }

    SECTION("Dereferencing iterator of begin")
    {
        forfun::experimental::container::list list{};

        list.push_back(1283);

        REQUIRE(*list.begin() == 1283);
    }

    SECTION("Dereferencing iterator and mutating dereferenced element")
    {
        forfun::experimental::container::list list{};

        list.push_back(1291);
        REQUIRE(*list.begin() == 1291);

        *list.begin() = 1297;

        REQUIRE(*list.begin() == 1297);
    }
}
