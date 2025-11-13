// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cmath>
#include <cstdint>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/factorial.hpp"

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::int8_t or larger type",
    "[factorial]",
    std::int32_t,
    std::int64_t
)
{
    SECTION("Factorial of negative")
    {
        // Undefined specification
    }

    SECTION("0! is one")
    {
        static constexpr auto const n{TestType{}};
        static constexpr auto const expected{TestType{1}};

        STATIC_REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        STATIC_REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        STATIC_REQUIRE(
            forfun::factorial::stl_functional::factorial(n) == expected
        );
    }

    SECTION("1! is one")
    {
        auto const volatile n{TestType{1}};
        static constexpr auto const expected{TestType{1}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        REQUIRE(forfun::factorial::stl_functional::factorial(n) == expected);
    }

    SECTION("5! is 120")
    {
        static constexpr auto const n{TestType{5}};
        static constexpr auto const expected{TestType{120}};

        STATIC_REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        STATIC_REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        STATIC_REQUIRE(
            forfun::factorial::stl_functional::factorial(n) == expected
        );
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::int16_t or larger type",
    "[factorial]",
    std::int16_t,
    std::int32_t,
    std::int64_t
)
{
    SECTION("7! is 5,040")
    {
        auto const volatile n{TestType{7}};
        static constexpr auto const expected{TestType{5'040}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::stl_functional::factorial(n) == expected);
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint16_t or larger type",
    "[factorial]",
    std::uint16_t,
    std::uint32_t
)
{
    SECTION("8! is 40,320")
    {
        auto const volatile n{TestType{8}};
        static constexpr auto const expected{TestType{40'320}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::stl_functional::factorial(n) == expected);
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint32_t or larger type",
    "[factorial]",
    std::uint32_t
)
{
    SECTION("12! is 479,001,600")
    {
        auto const volatile n{TestType{12}};
        static constexpr auto const expected{TestType{479'001'600}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        REQUIRE(forfun::factorial::stl_functional::factorial(n) == expected);
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint64_t or larger type",
    "[factorial]",
    std::uint64_t
)
{
    SECTION("20! is 2,432,902,008,176,640,000")
    {
        auto const volatile n{TestType{20}};
        static constexpr auto const expected{
            TestType{2'432'902'008'176'640'000}
        };

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        REQUIRE(forfun::factorial::stl_functional::factorial(n) == expected);
        REQUIRE(
            static_cast<TestType>(std::tgamma(n + TestType{1})) == expected
        );
    }
}
