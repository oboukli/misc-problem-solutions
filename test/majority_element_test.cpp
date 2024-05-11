// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <iterator>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/majority_element.hpp"

TEST_CASE("Majority element", "[majority_element]")
{
    using forfun::majority_element::majority_element;

    SECTION("Empty collection should have no majority")
    {
        constexpr std::array<int, 0> const elements{};

        STATIC_REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("One-element collection should have no majority")
    {
        constexpr std::array const elements{7};

        static_assert(elements.size() == 1);

        STATIC_REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("A collection of two unique elements should have no majority")
    {
        constexpr std::array const elements{5, 7};

        static_assert(elements.size() == 2);

        STATIC_REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("A collection of three unique elements should have no majority")
    {
        constexpr std::array const elements{3, 5, 7};

        CAPTURE(elements);

        REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("A collection of four unique elements should have no majority")
    {
        constexpr std::array const elements{3, 5, 7, 11};

        CAPTURE(elements);

        REQUIRE(majority_element(elements) == elements.cend());
    }

    SECTION("Left contiguous majority")
    {
        constexpr std::array const elements{11, 11, 11, 11, 13, 13, 13};
        using ConstItr = decltype(elements)::const_iterator;

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE_FALSE(result == elements.cend());
        CHECK(result == elements.cbegin());
        REQUIRE(*result == 11);
    }

    SECTION("Right contiguous majority")
    {
        constexpr std::array const elements{17, 17, 17, 19, 19, 19, 19};
        using ConstItr = decltype(elements)::const_iterator;

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE_FALSE(result == elements.cend());
        CHECK(result == std::next(elements.cbegin(), 6));
        REQUIRE(*result == 19);
    }

    SECTION("Equality among an odd number of elements of each group")
    {
        constexpr std::array const elements{5, 5, 5, 7, 7, 7};
        using ConstItr = decltype(elements)::const_iterator;

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE(result == elements.cend());
    }

    SECTION("Equality among an even number of elements of each group")
    {
        constexpr std::array const elements{5, 5, 5, 5, 7, 7, 7, 7};
        using ConstItr = decltype(elements)::const_iterator;

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE(result == elements.cend());
    }

    SECTION("Three elements with majority")
    {
        constexpr std::array const elements{1, 2, 1};
        using ConstItr = decltype(elements)::const_iterator;

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE_FALSE(result == elements.cend());
        CHECK(result == std::next(elements.cbegin(), 2));
        REQUIRE(*result == 1);
    }

    SECTION("Four elements with majority")
    {
        constexpr std::array const elements{2, 7, 2, 2};
        using ConstItr = decltype(elements)::const_iterator;

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE_FALSE(result == elements.cend());
        CHECK(result == std::next(elements.cbegin(), 2));
        REQUIRE(*result == 2);
    }

    SECTION("Eleven elements with majority")
    {
        constexpr std::array const elements{5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5};
        using ConstItr = decltype(elements)::const_iterator;

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE_FALSE(result == elements.cend());
        CHECK(result == std::next(elements.cbegin(), 10));
        REQUIRE(*result == 5);
    }

    SECTION("std::vector of eleven elements with majority")
    {
        std::vector const elements{5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5};

        CAPTURE(elements);

        auto const result{majority_element(elements)};

        REQUIRE_FALSE(result == elements.cend());
        CHECK(result == std::next(elements.cbegin(), 10));
        REQUIRE(*result == 5);
    }

    SECTION("Sixty-four elements with majority (benchmark case)")
    {
        constexpr std::array const elements{
            // clang-format off
            5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
            5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
            5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
            5, 7, 7, 7, 7, 5, 5, 7, 5, 5, 5, 7, 7, 5, 5, 5,
            // clang-format on
        };
        using ConstItr = decltype(elements)::const_iterator;

        static_assert(elements.size() == 64);

        CAPTURE(elements);

        ConstItr const result{majority_element(elements)};

        REQUIRE_FALSE(result == elements.cend());
        CHECK(result == std::next(elements.cbegin(), 24));
        REQUIRE(*result == 5);
    }
}
