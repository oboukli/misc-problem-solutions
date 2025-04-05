// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <cstddef>
#include <iterator>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/internal/list_iterator.hpp"
#include "forfun/container/list.hpp"

TEST_CASE("Linked list iterator traits", "[container][list][list_iterator]")
{
    // clang-format off
    static_assert(
        std::same_as<
            forfun::experimental::container::internal::list_iterator,
            forfun::experimental::container::list::iterator>
    );
    // clang-format on

    SECTION("Iterator")
    {
        using forfun::experimental::container::internal::list_iterator;

        STATIC_REQUIRE(std::bidirectional_iterator<list_iterator>);

        STATIC_REQUIRE(std::indirectly_writable<list_iterator, int>);
    }

    SECTION("Iterator traits")
    {
        using forfun::experimental::container::internal::list_iterator;

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_iterator>::iterator_category,
                std::bidirectional_iterator_tag>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_iterator>::iterator_concept,
                std::bidirectional_iterator_tag>
        );

        STATIC_REQUIRE(
            std::same_as<
                std::iterator_traits<list_iterator>::pointer,
                list_iterator>
        );

        STATIC_REQUIRE_FALSE(
            std::same_as<
                std::iterator_traits<list_iterator>::reference,
                std::iterator_traits<list_iterator>::const_reference>
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

        STATIC_REQUIRE(
            std::same_as<std::iter_difference_t<list_iterator>, std::ptrdiff_t>
        );

        STATIC_REQUIRE(std::same_as<std::iter_value_t<list_iterator>, int>);

        STATIC_REQUIRE(std::assignable_from<list_iterator::reference, int>);
    }
}
