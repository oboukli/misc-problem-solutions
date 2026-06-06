// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <concepts>

#include <catch2/catch_test_macros.hpp>

#include "forfun/common/type_traits.hpp"

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

TEST_CASE("Trait reference_conditional_const_t", "[type_traits]")
{
    using T = std::array<int, 0>;
    using ConstT = std::array<int, 0> const;

    SECTION("Positive")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::reference_conditional_const_t<T>,
                T::reference>
        );

        STATIC_REQUIRE(
            std::same_as<
                forfun::common::type_traits::reference_conditional_const_t<
                    ConstT>,
                T::const_reference>
        );
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(
            std::same_as<
                forfun::common::type_traits::reference_conditional_const_t<
                    ConstT>,
                T::reference>
        );

        STATIC_REQUIRE_FALSE(
            std::same_as<
                forfun::common::type_traits::reference_conditional_const_t<T>,
                T::const_reference>
        );
    }
}
