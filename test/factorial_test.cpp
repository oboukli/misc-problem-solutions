// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/factorial.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Factorial result supported by std::int8_t or larger type",
    "[factorial]",
    (auto factorial, factorial),
    forfun::factorial::iterative::factorial<std::int8_t>,
    forfun::factorial::recursive::factorial<std::int8_t>,
    forfun::factorial::stl_functional::factorial<std::int8_t>
)
{
    SECTION("0! is one")
    {
        static constexpr std::int8_t const expected{1};

        int const volatile n{};

        REQUIRE(factorial(n) == expected);
    }

    SECTION("1! is one")
    {
        static constexpr std::int8_t const expected{1};

        int const volatile n{1};

        REQUIRE(factorial(n) == expected);
    }

    SECTION("5! is 120")
    {
        static constexpr std::int8_t const expected{120};

        int const volatile n{5};

        REQUIRE(factorial(n) == expected);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Factorial result supported by std::int16_t or larger type",
    "[factorial]",
    (auto factorial, factorial),
    forfun::factorial::iterative::factorial<std::int16_t>,
    forfun::factorial::recursive::factorial<std::int16_t>,
    forfun::factorial::stl_functional::factorial<std::int16_t>
)
{
    SECTION("7! is 5,040")
    {
        static constexpr std::int16_t const expected{5'040};

        int const volatile n{7};

        REQUIRE(factorial(n) == expected);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Factorial result supported by std::uint16_t or larger type",
    "[factorial]",
    (auto factorial, factorial),
    forfun::factorial::iterative::factorial<std::uint16_t>,
    forfun::factorial::recursive::factorial<std::uint16_t>,
    forfun::factorial::stl_functional::factorial<std::uint16_t>
)
{
    SECTION("8! is 40,320")
    {
        static constexpr std::uint16_t const expected{40'320};

        int const volatile n{8};

        REQUIRE(factorial(n) == expected);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Factorial result supported by std::uint32_t or larger type",
    "[factorial]",
    (auto factorial, factorial),
    forfun::factorial::iterative::factorial<std::uint32_t>,
    forfun::factorial::recursive::factorial<std::uint32_t>,
    forfun::factorial::stl_functional::factorial<std::uint32_t>
)
{
    SECTION("12! is 479,001,600")
    {
        static constexpr std::uint32_t const expected{479'001'600};

        int const volatile n{12};

        REQUIRE(factorial(n) == expected);
    }
}

TEMPLATE_TEST_CASE_SIG(
    "Factorial result supported by std::uint64_t or larger type",
    "[factorial]",
    (auto factorial, factorial),
    forfun::factorial::iterative::factorial<std::uint64_t>,
    forfun::factorial::recursive::factorial<std::uint64_t>,
    forfun::factorial::stl_functional::factorial<std::uint64_t>
)
{
    SECTION("20! is 2,432,902,008,176,640,000")
    {
        static constexpr std::uint64_t const expected{
            2'432'902'008'176'640'000
        };

        int const volatile n{20};

        REQUIRE(factorial(n) == expected);
    }
}
