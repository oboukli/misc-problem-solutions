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

#include "forfun/container/internal/list_iterator.hpp"
#include "forfun/container/list.hpp"

TEST_CASE("Linked list iterator traits", "[container][list][list_iterator]")
{
    // clang-format off
    static_assert(
        std::same_as<
            forfun::container::internal::list_iterator,
            forfun::container::list::iterator>
    );
    // clang-format on

    SECTION("Iterator concepts")
    {
        using forfun::container::internal::list_iterator;

        STATIC_REQUIRE(std::bidirectional_iterator<list_iterator>);

        STATIC_REQUIRE(std::indirectly_writable<list_iterator, int>);
    }

    SECTION("Copy and move")
    {
        using forfun::container::internal::list_iterator;

        STATIC_REQUIRE(std::is_trivially_copy_constructible_v<list_iterator>);

        STATIC_REQUIRE(std::is_trivially_move_constructible_v<list_iterator>);

        STATIC_REQUIRE(std::is_trivially_copy_assignable_v<list_iterator>);

        STATIC_REQUIRE(std::is_trivially_move_assignable_v<list_iterator>);
    }

    SECTION("Traits")
    {
        using forfun::container::internal::list_iterator;

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_iterator>::iterator_category,
                std::bidirectional_iterator_tag>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_iterator>::pointer,
                std::add_pointer_t<int>>
        );

        STATIC_REQUIRE(
            std::same_as<std::iterator_traits<list_iterator>::reference, int&>
        );

        STATIC_REQUIRE(
            std::same_as<std::iter_reference_t<list_iterator>, int&>
        );

        STATIC_REQUIRE(
            std::same_as<std::iter_rvalue_reference_t<list_iterator>, int&&>
        );

        STATIC_REQUIRE(
            std::same_as<std::iter_common_reference_t<list_iterator>, int&>
        );

#if defined(__cpp_lib_ranges_as_const) && __cpp_lib_ranges_as_const >= 202207L
        STATIC_REQUIRE_FALSE(
            std::same_as<
                std::iter_reference_t<list_iterator>,
                std::iter_const_reference_t<list_iterator>>
        );

        STATIC_REQUIRE(
            std::same_as<std::iter_const_reference_t<list_iterator>, int const&>
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
                std::iterator_traits<list_iterator>::difference_type,
                std::ptrdiff_t>
        );

        STATIC_REQUIRE(
            std::same_as<std::iter_difference_t<list_iterator>, std::ptrdiff_t>
        );

        STATIC_REQUIRE(
            std::same_as<std::iterator_traits<list_iterator>::value_type, int>
        );

        STATIC_REQUIRE(std::same_as<std::iter_value_t<list_iterator>, int>);
    }
}
