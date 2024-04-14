// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_message.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/factorial.hpp"

#if FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE
#define FORFUN_REQUIRE_STL_FUNCTIONAL(X) \
    REQUIRE(forfun::factorial::stl_functional::factorial(n) == X)
#define FORFUN_STATIC_REQUIRE_STL_FUNCTIONAL(X) \
    STATIC_REQUIRE(forfun::factorial::stl_functional::factorial(n) == X)
#else
#define FORFUN_REQUIRE_STL_FUNCTIONAL(X)
#define FORFUN_STATIC_REQUIRE_STL_FUNCTIONAL(X)
#endif // FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE

TEST_CASE("Compiler feature test", "[factorial]")
{
#if FORFUN_FACTORIAL_STL_FUNCTIONAL_AVAILABLE
    INFO("forfun::factorial::stl_functional::factorial<>(n) is available");
#else
    WARN(
        "forfun::factorial::stl_functional::factorial<>(n) is not available "
        "because it was not supported by the C++ compiler.");
#endif // FORFUN_UNSUPPORTED_FEATURE
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::int8_t or larger type",
    "[factorial]",
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
        static constexpr auto const expected{TestType{1}};

        STATIC_REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        STATIC_REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        FORFUN_STATIC_REQUIRE_STL_FUNCTIONAL(expected);
    }

    SECTION("1! is one")
    {
        auto const volatile n{TestType{1}};
        static constexpr auto const expected{TestType{1}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        FORFUN_REQUIRE_STL_FUNCTIONAL(expected);
    }

    SECTION("5! is 120")
    {
        static constexpr auto const n{TestType{5}};
        static constexpr auto const expected{TestType{120}};

        STATIC_REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        STATIC_REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        FORFUN_STATIC_REQUIRE_STL_FUNCTIONAL(expected);
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::int16_t or larger type",
    "[factorial]",
    std::int16_t,
    std::int32_t,
    std::int64_t)
{
    SECTION("7! is 5,040")
    {
        auto const volatile n{TestType{7}};
        static constexpr auto const expected{TestType{5'040}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        FORFUN_REQUIRE_STL_FUNCTIONAL(expected);
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint16_t or larger type",
    "[factorial]",
    std::uint16_t,
    std::uint32_t)
{
    SECTION("8! is 40,320")
    {
        auto const volatile n{TestType{8}};
        static constexpr auto const expected{TestType{40'320}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        FORFUN_REQUIRE_STL_FUNCTIONAL(expected);
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint32_t or larger type",
    "[factorial]",
    std::uint32_t)
{
    SECTION("12! is 479,001,600")
    {
        auto const volatile n{TestType{12}};
        static constexpr auto const expected{TestType{479'001'600}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        FORFUN_REQUIRE_STL_FUNCTIONAL(expected);
    }
}

TEMPLATE_TEST_CASE(
    "Factorial value supported by std::uint64_t or larger type",
    "[factorial]",
    std::uint64_t)
{
    SECTION("20! is 2,432,902,008,176,640,000")
    {
        auto const volatile n{TestType{20}};
        static constexpr auto const expected{
            TestType{2'432'902'008'176'640'000}};

        REQUIRE(forfun::factorial::iterative::factorial(n) == expected);
        REQUIRE(forfun::factorial::recursive::factorial(n) == expected);
        FORFUN_REQUIRE_STL_FUNCTIONAL(expected);
    }
}
