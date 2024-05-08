// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cassert>
#include <stack>

#include <catch2/catch_test_macros.hpp>

#include "forfun/tower_of_hanoi.hpp"

namespace {

constexpr auto
push_range(auto& dest_container, auto const& src_list) noexcept -> void
    requires requires { dest_container.push_range(src_list); }
{
    dest_container.push_range(src_list);
}

constexpr auto
push_range(auto& dest_container, auto const& src_list) noexcept -> void
{
    for (auto const e : src_list)
    {
        dest_container.push(e);
    }
}

} // namespace

TEST_CASE("Tower of Hanoi", "[tower_of_hanoi]")
{
    using forfun::tower_of_hanoi::recursive::toh;

    auto const monk{
        [](std::stack<int>& src, std::stack<int>& des) noexcept -> void {
            assert(src.empty() == false);

            des.push(src.top());
            src.pop();
        }};

    SECTION("Empty")
    {
        std::stack<int> src_rod{};
        std::stack<int> des_rod{};
        std::stack<int> aux_rod{};

        assert(src_rod.empty());
        assert(des_rod.empty());
        assert(aux_rod.empty());

        std::stack<int> expected{};

        toh(src_rod, des_rod, aux_rod, monk, src_rod.size());

        REQUIRE(src_rod.empty());
        REQUIRE(des_rod.empty());
        REQUIRE(aux_rod.empty());
    }

    SECTION("One disk")
    {
        std::stack<int> src_rod{};
        auto const disks = {1};
        push_range(src_rod, disks);

        std::stack<int> des_rod{};
        std::stack<int> aux_rod{};

        assert(src_rod.size() == 1);
        assert(src_rod.top() == 1);
        assert(des_rod.empty());
        assert(aux_rod.empty());

        std::stack<int> expected{};
        push_range(expected, disks);

        toh(src_rod, des_rod, aux_rod, monk, src_rod.size());

        REQUIRE(src_rod.empty());
        REQUIRE(des_rod.size() == 1);
        REQUIRE(des_rod.top() == expected.top());
        REQUIRE(aux_rod.empty());
    }

    SECTION("Two disks")
    {
        std::stack<int> src_rod{};
        auto const disks = {2, 1};
        push_range(src_rod, disks);

        std::stack<int> des_rod{};
        std::stack<int> aux_rod{};

        assert(src_rod.size() == 2);
        assert(src_rod.top() == 1);
        assert(des_rod.empty());
        assert(aux_rod.empty());

        std::stack<int> expected{};
        push_range(expected, disks);

        toh(src_rod, des_rod, aux_rod, monk, src_rod.size());

        REQUIRE(src_rod.empty());
        REQUIRE(des_rod.size() == 2);
        REQUIRE(des_rod.top() == expected.top());
        REQUIRE(aux_rod.empty());
    }

    SECTION("Three disks")
    {
        std::stack<int> src_rod{};
        auto const disks = {3, 2, 1};
        push_range(src_rod, disks);

        std::stack<int> des_rod{};
        std::stack<int> aux_rod{};

        assert(src_rod.size() == 3);
        assert(src_rod.top() == 1);
        assert(des_rod.empty());
        assert(aux_rod.empty());

        std::stack<int> expected{};
        push_range(expected, disks);

        toh(src_rod, des_rod, aux_rod, monk, src_rod.size());

        REQUIRE(src_rod.empty());
        REQUIRE(des_rod.size() == 3);
        REQUIRE(des_rod.top() == expected.top());
        REQUIRE(aux_rod.empty());
    }

    SECTION("Four disks")
    {
        std::stack<int> src_rod{};
        auto const disks = {4, 3, 2, 1};
        push_range(src_rod, disks);

        std::stack<int> des_rod{};
        std::stack<int> aux_rod{};

        assert(src_rod.size() == 4);
        assert(src_rod.top() == 1);
        assert(des_rod.empty());
        assert(aux_rod.empty());

        std::stack<int> expected{};
        push_range(expected, disks);

        toh(src_rod, des_rod, aux_rod, monk, src_rod.size());

        REQUIRE(src_rod.empty());
        REQUIRE(des_rod.size() == 4);
        REQUIRE(des_rod.top() == expected.top());
        REQUIRE(aux_rod.empty());
    }

    SECTION("Move count")
    {
        SECTION("Given no disk then no moves")
        {
            static constexpr unsigned int const num_disks{0};

            int src_rod{};
            int des_rod{};
            int aux_rod{};
            unsigned int count{0};

            forfun::tower_of_hanoi::recursive::toh(
                src_rod,
                des_rod,
                aux_rod,
                [&count](int&, int&) noexcept -> void { ++count; },
                num_disks);

            REQUIRE(count == 0);
        }

        SECTION("Given one disk then one move")
        {
            static constexpr unsigned int const num_disks{1};

            int src_rod{};
            int des_rod{};
            int aux_rod{};
            unsigned int count{0};

            forfun::tower_of_hanoi::recursive::toh(
                src_rod,
                des_rod,
                aux_rod,
                [&count](int&, int&) noexcept -> void { ++count; },
                num_disks);

            REQUIRE(count == 1);
        }

        SECTION("Given two disks then three moves")
        {
            static constexpr unsigned int const num_disks{2};

            int src_rod{};
            int des_rod{};
            int aux_rod{};
            unsigned int count{0};

            forfun::tower_of_hanoi::recursive::toh(
                src_rod,
                des_rod,
                aux_rod,
                [&count](int&, int&) noexcept -> void { ++count; },
                num_disks);

            REQUIRE(count == 3);
        }

        SECTION("Given four disks then fifteen moves")
        {
            static constexpr unsigned int const num_disks{4};

            int src_rod{};
            int des_rod{};
            int aux_rod{};
            unsigned int count{0};

            forfun::tower_of_hanoi::recursive::toh(
                src_rod,
                des_rod,
                aux_rod,
                [&count](int&, int&) noexcept -> void { ++count; },
                num_disks);

            REQUIRE(count == 15);
        }
    }

    SECTION("Exception specification")
    {
        SECTION("noexcept(false)")
        {
            int src_rod{};
            int des_rod{};
            int aux_rod{};

            STATIC_REQUIRE_FALSE(
                noexcept(forfun::tower_of_hanoi::recursive::toh(
                    src_rod,
                    des_rod,
                    aux_rod,
                    [](int&, int&) noexcept(false) -> void {},
                    0)));
        }

        SECTION("noexcept(true)")
        {
            int src_rod{};
            int des_rod{};
            int aux_rod{};

            STATIC_REQUIRE(noexcept(forfun::tower_of_hanoi::recursive::toh(
                src_rod,
                des_rod,
                aux_rod,
                [](int&, int&) noexcept -> void {},
                0)));
        }
    }
}
