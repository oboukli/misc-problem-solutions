// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <cstddef>
#include <iterator>
#include <type_traits>

#if !defined(__cpp_lib_ranges_as_const) || __cpp_lib_ranges_as_const < 202207L
#include <catch2/catch_message.hpp>
#endif // !defined(__cpp_lib_ranges_as_const) || __cpp_lib_ranges_as_const <
       // 202207L

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/internal/list_const_iterator.hpp"
#include "forfun/container/list.hpp"

TEST_CASE(
    "Linked list iterator traits", "[container][list][list_const_iterator]"
)
{
    // clang-format off
    static_assert(
        std::same_as<
            forfun::container::internal::list_const_iterator,
            forfun::container::list::const_iterator>);
    // clang-format on

    SECTION("Iterator concepts")
    {
        using forfun::container::internal::list_const_iterator;

        STATIC_REQUIRE(std::bidirectional_iterator<list_const_iterator>);

        STATIC_REQUIRE_FALSE(
            std::indirectly_writable<list_const_iterator, int>
        );
    }

    SECTION("Copy and move")
    {
        using forfun::container::internal::list_const_iterator;

        STATIC_REQUIRE(
            std::is_trivially_copy_constructible_v<list_const_iterator>
        );

        STATIC_REQUIRE(
            std::is_trivially_move_constructible_v<list_const_iterator>
        );

        STATIC_REQUIRE(
            std::is_trivially_copy_assignable_v<list_const_iterator>
        );

        STATIC_REQUIRE(
            std::is_trivially_move_assignable_v<list_const_iterator>
        );
    }

    SECTION("Traits")
    {
        using forfun::container::internal::list_const_iterator;

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_const_iterator>::iterator_category,
                std::bidirectional_iterator_tag>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_const_iterator>::pointer,
                std::add_pointer_t<std::add_const_t<int>>>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_const_iterator>::reference,
                std::add_lvalue_reference_t<std::add_const_t<int>>>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iter_reference_t<list_const_iterator>,
                std::add_lvalue_reference_t<std::add_const_t<int>>>
        );

        STATIC_REQUIRE_FALSE(
            std::same_as<
                std::iter_rvalue_reference_t<list_const_iterator>,
                int&&>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iter_common_reference_t<list_const_iterator>,
                std::add_lvalue_reference_t<std::add_const_t<int>>>
        );

#if defined(__cpp_lib_ranges_as_const) && __cpp_lib_ranges_as_const >= 202207L
        STATIC_REQUIRE(
            std::same_as<
                std::iter_const_reference_t<list_const_iterator>,
                std::add_lvalue_reference_t<std::add_const_t<int>>>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iter_reference_t<list_const_iterator>,
                std::iter_const_reference_t<list_const_iterator>>
        );
#else
        WARN(
            "Skipped a test because std::iter_const_reference_t "
            "is not supported by the referenced C++ standard library."
        );
#endif // defined(__cpp_lib_ranges_as_const) && __cpp_lib_ranges_as_const >=
       // 202207L

        STATIC_REQUIRE(
            std::same_as<
                std::iter_difference_t<list_const_iterator>,
                std::ptrdiff_t>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_const_iterator>::difference_type,
                std::ptrdiff_t>
        );

        STATIC_REQUIRE(
            std::same_as<std::iter_value_t<list_const_iterator>, int>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_const_iterator>::value_type,
                int>
        );

        STATIC_REQUIRE_FALSE(
            std::assignable_from<list_const_iterator::const_reference, int>
        );
    }
}
