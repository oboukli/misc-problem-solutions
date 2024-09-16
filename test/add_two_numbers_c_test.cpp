// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <memory>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun_c/add_two_numbers.h"
#include "forfun_c/container/forward_list.h"

TEMPLATE_TEST_CASE_SIG(
    "Add two numbers",
    "[add_two_numbers][dynamic_allocation]",
    (auto add_two_numbers, add_two_numbers),
    &::forfun_iterative_add_two_numbers
)
{
    using ::forfun_forward_list_node;
    using ::forfun_free_node_list;

    using node_ptr = std::unique_ptr<
        ::forfun_forward_list_node,
        decltype(&::forfun_free_node_list)>;

    SECTION("0 + 0")
    {
        forfun_forward_list_node const node_a = {.next = nullptr, .value = 0U};

        forfun_forward_list_node const node_b = {.next = nullptr, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 0U);
        REQUIRE(actual->next == nullptr);
    }

    SECTION("0 + 1")
    {
        forfun_forward_list_node const node_a = {.next = nullptr, .value = 0U};

        forfun_forward_list_node const node_b = {.next = nullptr, .value = 1U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 1U);
        REQUIRE(actual->next == nullptr);
    }

    SECTION("1 + 0")
    {
        forfun_forward_list_node const node_a = {.next = nullptr, .value = 1U};

        forfun_forward_list_node const node_b = {.next = nullptr, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 1U);
        REQUIRE(actual->next == nullptr);
    }

    SECTION("1 + 1")
    {
        forfun_forward_list_node const node_a = {.next = nullptr, .value = 1U};

        forfun_forward_list_node const node_b = {.next = nullptr, .value = 1U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 2U);
        REQUIRE(actual->next == nullptr);
    }

    SECTION("3 + 7")
    {
        forfun_forward_list_node const node_a = {.next = nullptr, .value = 3U};

        forfun_forward_list_node const node_b = {.next = nullptr, .value = 7U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 0U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 1U);
        REQUIRE(actual->next->next == nullptr);
    }

    SECTION("1 + 10")
    {
        forfun_forward_list_node const node_a = {.next = nullptr, .value = 1U};

        forfun_forward_list_node node_b_1 = {.next = nullptr, .value = 1U};
        forfun_forward_list_node const node_b_0
            = {.next = &node_b_1, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b_0), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 1U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 1U);
        REQUIRE(actual->next->next == nullptr);
    }

    SECTION("100 + 100")
    {
        forfun_forward_list_node node_a_2 = {.next = nullptr, .value = 1U};
        forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 0U};
        forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 0U};

        forfun_forward_list_node node_b_2 = {.next = nullptr, .value = 1U};
        forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 0U};
        forfun_forward_list_node const node_b_0
            = {.next = &node_b_1, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a_0, &node_b_0), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 0U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 0U);
        REQUIRE_FALSE(actual->next->next == nullptr);

        REQUIRE(actual->next->next->value == 2U);
        REQUIRE(actual->next->next->next == nullptr);
    }

    SECTION("100 + 910")
    {
        forfun_forward_list_node node_a_2 = {.next = nullptr, .value = 1U};
        forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 0U};
        forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 0U};

        forfun_forward_list_node node_b_2 = {.next = nullptr, .value = 9U};
        forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 1U};
        forfun_forward_list_node const node_b_0
            = {.next = &node_b_1, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a_0, &node_b_0), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 0U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 1U);
        REQUIRE_FALSE(actual->next->next == nullptr);

        REQUIRE(actual->next->next->value == 0U);
        REQUIRE_FALSE(actual->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->value == 1U);
        REQUIRE(actual->next->next->next->next == nullptr);
    }

    SECTION("342 + 465 = 807 (LeetCode test case)")
    {
        forfun_forward_list_node node_a_2 = {.next = nullptr, .value = 3U};
        forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 4U};
        forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 2U};

        forfun_forward_list_node node_b_2 = {.next = nullptr, .value = 4U};
        forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 6U};
        forfun_forward_list_node const node_b_0
            = {.next = &node_b_1, .value = 5U};

        node_ptr const actual{
            add_two_numbers(&node_a_0, &node_b_0), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 7U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 0U);
        REQUIRE_FALSE(actual->next->next == nullptr);

        REQUIRE(actual->next->next->value == 8U);
        REQUIRE(actual->next->next->next == nullptr);
    }

    SECTION("9999999 + 9999 = 10009998 (LeetCode test case)")
    {
        forfun_forward_list_node node_a_6 = {.next = nullptr, .value = 9U};
        forfun_forward_list_node node_a_5 = {.next = &node_a_6, .value = 9U};
        forfun_forward_list_node node_a_4 = {.next = &node_a_5, .value = 9U};
        forfun_forward_list_node node_a_3 = {.next = &node_a_4, .value = 9U};
        forfun_forward_list_node node_a_2 = {.next = &node_a_3, .value = 9U};
        forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 9U};
        forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 9U};

        forfun_forward_list_node node_b_3 = {.next = nullptr, .value = 9U};
        forfun_forward_list_node node_b_2 = {.next = &node_b_3, .value = 9U};
        forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 9U};
        forfun_forward_list_node const node_b_0
            = {.next = &node_b_1, .value = 9U};

        node_ptr const actual{
            add_two_numbers(&node_a_0, &node_b_0), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 8U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 9U);
        REQUIRE_FALSE(actual->next->next == nullptr);

        REQUIRE(actual->next->next->value == 9U);
        REQUIRE_FALSE(actual->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->value == 9U);
        REQUIRE_FALSE(actual->next->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->next->value == 0U);
        REQUIRE_FALSE(actual->next->next->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->next->next->value == 0U);
        REQUIRE_FALSE(actual->next->next->next->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->next->next->next->value == 0U);
        REQUIRE_FALSE(
            actual->next->next->next->next->next->next->next == nullptr
        );

        REQUIRE(actual->next->next->next->next->next->next->next->value == 1U);
        REQUIRE(
            actual->next->next->next->next->next->next->next->next == nullptr
        );
    }

    SECTION("256541 + 997991 = 1254532 (benchmark case)")
    {
        forfun_forward_list_node node_a_5 = {.next = nullptr, .value = 2U};
        forfun_forward_list_node node_a_4 = {.next = &node_a_5, .value = 5U};
        forfun_forward_list_node node_a_3 = {.next = &node_a_4, .value = 6U};
        forfun_forward_list_node node_a_2 = {.next = &node_a_3, .value = 5U};
        forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 4U};
        forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 1U};

        forfun_forward_list_node node_b_5 = {.next = nullptr, .value = 9U};
        forfun_forward_list_node node_b_4 = {.next = &node_b_5, .value = 9U};
        forfun_forward_list_node node_b_3 = {.next = &node_b_4, .value = 7U};
        forfun_forward_list_node node_b_2 = {.next = &node_b_3, .value = 9U};
        forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 9U};
        forfun_forward_list_node const node_b_0
            = {.next = &node_b_1, .value = 1U};

        node_ptr const actual{
            add_two_numbers(&node_a_0, &node_b_0), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 2U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 3U);
        REQUIRE_FALSE(actual->next->next == nullptr);

        REQUIRE(actual->next->next->value == 5U);
        REQUIRE_FALSE(actual->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->value == 4U);
        REQUIRE_FALSE(actual->next->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->next->value == 5U);
        REQUIRE_FALSE(actual->next->next->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->next->next->value == 2U);
        REQUIRE_FALSE(actual->next->next->next->next->next->next == nullptr);

        REQUIRE(actual->next->next->next->next->next->next->value == 1U);
        REQUIRE(actual->next->next->next->next->next->next->next == nullptr);
    }
}
