// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>

#include <catch2/catch_test_macros.hpp>

#include "forfun/common/type_traits.hpp"

TEST_CASE("Trait conditional_const_t", "[type_traits]")
{
    SECTION("Should be const")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    conditional_const_t<char const, int>,
                int const>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    conditional_const_t<char const&, int>,
                int const>
        );
    }

    SECTION("Should not be const")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::conditional_const_t<char, int>,
                int>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::conditional_const_t<char&, int>,
                int>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::conditional_const_t<char&&, int>,
                int>
        );
    }
}

TEST_CASE("Trait forward_like_t", "[type_traits]")
{
    SECTION("Should add reference")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::forward_like_t<char, int>,
                int&&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::forward_like_t<char&, int>,
                int&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::forward_like_t<char&&, int>,
                int&&>
        );
    }

    SECTION("Should add const")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::forward_like_t<char const, int>,
                int const&&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::forward_like_t<char const&, int>,
                int const&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::forward_like_t<char const&&, int>,
                int const&&>
        );
    }

    SECTION("Should remove volatile")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::forward_like_t<char volatile, int>,
                int&&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    forward_like_t<char volatile&, int>,
                int&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    forward_like_t<char volatile&&, int>,
                int&&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    forward_like_t<char const volatile, int>,
                int const&&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    forward_like_t<char const volatile&, int>,
                int const&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    forward_like_t<char const volatile&&, int>,
                int const&&>
        );
    }
}

TEST_CASE("Trait if_const_t", "[type_traits]")
{
    SECTION("Positive cases")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::if_const_t<int const, char, bool>,
                char>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::if_const_t<int const&, char, bool>,
                char>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    if_const_t<int const&&, char, bool>,
                char>
        );
    }

    SECTION("Negative cases")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::if_const_t<int, char, bool>,
                bool>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::if_const_t<int&, char, bool>,
                bool>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::if_const_t<int&&, char, bool>,
                bool>
        );
    }
}

TEST_CASE("Trait reference_conditional_const_t", "[type_traits]")
{
    SECTION("Should be const")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    reference_conditional_const_t<char const, int>,
                int const&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    reference_conditional_const_t<char const&, int>,
                int const&>
        );
    }

    SECTION("Should not be const")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    reference_conditional_const_t<char, int>,
                int&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    reference_conditional_const_t<char&, int>,
                int&>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::
                    reference_conditional_const_t<char&&, int>,
                int&>
        );
    }
}

TEST_CASE("Trait type_is_one_of_v", "[type_traits]")
{
    SECTION("Positive")
    {
        STATIC_REQUIRE(
            forfun::common::type_traits::
                type_is_one_of_v<char, char, float, int>
        );

        STATIC_REQUIRE(
            forfun::common::type_traits::type_is_one_of_v<int, char, float, int>
        );

        STATIC_REQUIRE(
            forfun::common::type_traits::
                type_is_one_of_v<float, char, float, int>
        );
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(
            forfun::common::type_traits::
                type_is_one_of_v<short, char, float, int>
        );

        STATIC_REQUIRE_FALSE(
            forfun::common::type_traits::
                type_is_one_of_v<double, char, float, int>
        );
    }
}
