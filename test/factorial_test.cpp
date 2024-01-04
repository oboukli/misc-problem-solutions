// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/factorial.hpp"

using forfun::factorial::iterative::factorial;

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::int8_t or larger",
    "[factorial]",
    std::int8_t,
    std::int16_t,
    std::int32_t,
    std::int64_t)
{
    SECTION("Factorial of negative")
    {
        // Undefined specification
    }

    SECTION("0! is one")
    {
        static constexpr auto const n{TestType{0}};

        auto const result{factorial(n)};

        STATIC_REQUIRE(result == TestType{1});
    }

    SECTION("1! is one")
    {
        auto const volatile n{TestType{1}};

        auto const result{factorial(n)};

        REQUIRE(result == TestType{1});
    }

    SECTION("5! is 120")
    {
        static constexpr auto const n{TestType{5}};

        auto const result{factorial(n)};

        STATIC_REQUIRE(result == TestType{120});
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::int16_t or larger",
    "[factorial]",
    std::int16_t,
    std::int32_t,
    std::int64_t)
{
    SECTION("7! is 5,040")
    {
        auto const volatile n{TestType{7}};

        auto const result{factorial(n)};

        REQUIRE(result == TestType{5'040});
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint16_t or larger",
    "[factorial]",
    std::uint16_t,
    std::uint32_t)
{
    SECTION("8! is 40,320")
    {
        auto const volatile n{TestType{8}};

        auto const result{factorial(n)};

        REQUIRE(result == TestType{40'320});
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint32_t or larger",
    "[factorial]",
    std::uint32_t)
{
    SECTION("12! is 479,001,600")
    {
        auto const volatile n{TestType{12}};

        auto const result{factorial(n)};

        REQUIRE(result == TestType{479'001'600});
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value by std::uint64_t or larger", "[factorial]", std::uint64_t)
{
    SECTION("20! is 2,432,902,008,176,640,000")
    {
        auto const volatile n{TestType{20}};

        auto const result{factorial(n)};

        REQUIRE(result == std::uint64_t{2'432'902'008'176'640'000});
    }
}
