// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdlib>
#include <memory>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun_c/mem/mem.h"
#include "forfun_c/shim/allocator.h"

#include "forfun_c/add_two_numbers.h"
#include "forfun_c/container/forward_list.h"

namespace {

class shim_scoped_guard final {
public:
    shim_scoped_guard() : is_valid_{::forfun_shim_enable() == 0}
    {
    }

    ~shim_scoped_guard()
    {
        ::forfun_shim_disable();
    }

    shim_scoped_guard(shim_scoped_guard const&) = delete;

    shim_scoped_guard(shim_scoped_guard&&) = delete;

    auto operator=(shim_scoped_guard const&) -> shim_scoped_guard& = delete;

    auto operator=(shim_scoped_guard&&) -> shim_scoped_guard& = delete;

    [[nodiscard]] auto is_valid() const noexcept -> bool
    {
        return is_valid_;
    }

private:
    bool is_valid_;
};

struct shim_context_scoped_guard final {
    shim_context_scoped_guard()
    {
        ::forfun_shim_reset();
    }

    ~shim_context_scoped_guard()
    {
        ::forfun_shim_reset();
    }

    shim_context_scoped_guard(shim_context_scoped_guard const&) = delete;

    shim_context_scoped_guard(shim_context_scoped_guard&&) = delete;

    auto operator=(shim_context_scoped_guard const&)
        -> shim_context_scoped_guard& = delete;

    auto operator=(shim_context_scoped_guard&&)
        -> shim_context_scoped_guard& = delete;
};

} // namespace

TEMPLATE_TEST_CASE_SIG(
    "Add two numbers (shimmed)",
    "[add_two_numbers][dynamic_allocation]",
    (auto add_two_numbers, add_two_numbers),
    &::forfun_iterative_add_two_numbers,
    &::forfun_recursive_add_two_numbers
)
{
    using ::forfun_forward_list_node;
    using ::forfun_free_node_list;

    using node_ptr = std::unique_ptr<
        ::forfun_forward_list_node,
        decltype(&::forfun_free_node_list)>;

    shim_scoped_guard shim_guard;
    REQUIRE(shim_guard.is_valid());

    SECTION("0 + 0")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 0U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 0U);
        REQUIRE(actual->next == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{1});
    }

    SECTION("0 + 1")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 0U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 1U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 1U);
        REQUIRE(actual->next == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{1});
    }

    SECTION("1 + 0")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 1U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 1U);
        REQUIRE(actual->next == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{1});
    }

    SECTION("1 + 1")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 1U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 1U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 2U);
        REQUIRE(actual->next == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{1});
    }

    SECTION("3 + 7")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 3U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 7U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 0U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 1U);
        REQUIRE(actual->next->next == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{2});
    }

    SECTION("1 + 10")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 1U};

        ::forfun_forward_list_node node_b_1 = {.next = nullptr, .value = 1U};
        ::forfun_forward_list_node const node_b_0
            = {.next = &node_b_1, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b_0), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 1U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 1U);
        REQUIRE(actual->next->next == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{2});
    }

    SECTION("100 + 100")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node node_a_2 = {.next = nullptr, .value = 1U};
        ::forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 0U};
        ::forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 0U};

        ::forfun_forward_list_node node_b_2 = {.next = nullptr, .value = 1U};
        ::forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 0U};
        ::forfun_forward_list_node const node_b_0
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

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{3});
    }

    SECTION("100 + 910")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node node_a_2 = {.next = nullptr, .value = 1U};
        ::forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 0U};
        ::forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 0U};

        ::forfun_forward_list_node node_b_2 = {.next = nullptr, .value = 9U};
        ::forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 1U};
        ::forfun_forward_list_node const node_b_0
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

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{4});
    }

    SECTION("342 + 465 = 807 (LeetCode test case)")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node node_a_2 = {.next = nullptr, .value = 3U};
        ::forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 4U};
        ::forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 2U};

        ::forfun_forward_list_node node_b_2 = {.next = nullptr, .value = 4U};
        ::forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 6U};
        ::forfun_forward_list_node const node_b_0
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

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{3});
    }

    SECTION("9999999 + 9999 = 10009998 (LeetCode test case)")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node node_a_6 = {.next = nullptr, .value = 9U};
        ::forfun_forward_list_node node_a_5 = {.next = &node_a_6, .value = 9U};
        ::forfun_forward_list_node node_a_4 = {.next = &node_a_5, .value = 9U};
        ::forfun_forward_list_node node_a_3 = {.next = &node_a_4, .value = 9U};
        ::forfun_forward_list_node node_a_2 = {.next = &node_a_3, .value = 9U};
        ::forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 9U};
        ::forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 9U};

        ::forfun_forward_list_node node_b_3 = {.next = nullptr, .value = 9U};
        ::forfun_forward_list_node node_b_2 = {.next = &node_b_3, .value = 9U};
        ::forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 9U};
        ::forfun_forward_list_node const node_b_0
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

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{8});
    }

    SECTION("256541 + 997991 = 1254532 (benchmark case)")
    {
        shim_context_scoped_guard shim_context_guard;
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node node_a_5 = {.next = nullptr, .value = 2U};
        ::forfun_forward_list_node node_a_4 = {.next = &node_a_5, .value = 5U};
        ::forfun_forward_list_node node_a_3 = {.next = &node_a_4, .value = 6U};
        ::forfun_forward_list_node node_a_2 = {.next = &node_a_3, .value = 5U};
        ::forfun_forward_list_node node_a_1 = {.next = &node_a_2, .value = 4U};
        ::forfun_forward_list_node const node_a_0
            = {.next = &node_a_1, .value = 1U};

        ::forfun_forward_list_node node_b_5 = {.next = nullptr, .value = 9U};
        ::forfun_forward_list_node node_b_4 = {.next = &node_b_5, .value = 9U};
        ::forfun_forward_list_node node_b_3 = {.next = &node_b_4, .value = 7U};
        ::forfun_forward_list_node node_b_2 = {.next = &node_b_3, .value = 9U};
        ::forfun_forward_list_node node_b_1 = {.next = &node_b_2, .value = 9U};
        ::forfun_forward_list_node const node_b_0
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

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{7});
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Add two numbers (shimmed memory allocation failure cases)",
    "[add_two_numbers][dynamic_allocation]",
    (auto add_two_numbers, add_two_numbers),
    &::forfun_iterative_add_two_numbers,
    &::forfun_recursive_add_two_numbers
)
{
    using ::forfun_forward_list_node;
    using ::forfun_free_node_list;

    using node_ptr = std::unique_ptr<
        ::forfun_forward_list_node,
        decltype(&::forfun_free_node_list)>;

    shim_scoped_guard shim_guard;
    REQUIRE(shim_guard.is_valid());

    SECTION("0 + 0")
    {
        shim_context_scoped_guard shim_context_guard;
        ::forfun_shim_set_malloc_fail_after(0);
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 0U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 0U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE(actual == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{1});
    }

    SECTION("3 + 7")
    {
        shim_context_scoped_guard shim_context_guard;
        ::forfun_shim_set_malloc_fail_after(1);
        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{0});

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 3U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 7U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE(actual == nullptr);

        REQUIRE(::forfun_shim_get_malloc_call_count() == std::size_t{2});
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Add two numbers (unshimmed)",
    "[add_two_numbers][dynamic_allocation]",
    (auto add_two_numbers, add_two_numbers),
    &::forfun_iterative_add_two_numbers,
    &::forfun_recursive_add_two_numbers
)
{
    using ::forfun_forward_list_node;
    using ::forfun_free_node_list;

    using node_ptr = std::unique_ptr<
        ::forfun_forward_list_node,
        decltype(&::forfun_free_node_list)>;

    ::forfun_mem_reset_to_default();

    SECTION("5 + 7")
    {
        auto const m{::forfun_mem_get()};

        REQUIRE(m.ff_malloc == &std::malloc);
        REQUIRE(m.ff_free == &std::free);

        ::forfun_forward_list_node const node_a
            = {.next = nullptr, .value = 5U};

        ::forfun_forward_list_node const node_b
            = {.next = nullptr, .value = 7U};

        node_ptr const actual{
            add_two_numbers(&node_a, &node_b), &::forfun_free_node_list
        };

        REQUIRE_FALSE(actual == nullptr);

        REQUIRE(actual->value == 2U);
        REQUIRE_FALSE(actual->next == nullptr);

        REQUIRE(actual->next->value == 1U);
        REQUIRE(actual->next->next == nullptr);
    }
}
