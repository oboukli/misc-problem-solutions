// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/factorial.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Factorial",
    "[factorial]",
    (auto factorial, factorial),
    forfun::factorial::iterative::factorial<int>,
    forfun::factorial::recursive::factorial<int>,
    forfun::factorial::stl_functional::factorial<int>
)
{
    SECTION("0! is one")
    {
        static constexpr int const expected{1};
        static constexpr int const n{};

        STATIC_REQUIRE(factorial(n) == expected);
    }

    SECTION("1! is one")
    {
        static constexpr int const expected{1};
        static constexpr int const n{1};

        STATIC_REQUIRE(factorial(n) == expected);
    }

    SECTION("5! is 120")
    {
        static constexpr int const expected{120};
        static constexpr int const n{5};

        STATIC_REQUIRE(factorial(n) == expected);
    }
}

TEST_CASE("Factorial (metaprogramming)", "[factorial]")
{
    SECTION("0! is one")
    {
        static constexpr int const expected{1};
        static constexpr int const n{};

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::classic::factorial_v<n, int>
            == expected
        );

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::modern::factorial_v<n, int>
            == expected
        );
    }

    SECTION("1! is one")
    {
        static constexpr int const expected{1};
        static constexpr int const n{1};

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::classic::factorial_v<n, int>
            == expected
        );

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::modern::factorial_v<n, int>
            == expected
        );
    }

    SECTION("5! is 120")
    {
        static constexpr int const expected{120};
        static constexpr int const n{5};

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::classic::factorial_v<n, int>
            == expected
        );

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::modern::factorial_v<n, int>
            == expected
        );
    }

    SECTION("5! is 120 (std::int16_t)")
    {
        static constexpr std::int16_t const expected{120};
        static constexpr int const n{5};

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::classic::
                factorial_v<n, std::int16_t>
            == expected
        );

        STATIC_REQUIRE(
            forfun::factorial::metaprogramming::modern::
                factorial_v<n, std::int16_t>
            == expected
        );
    }
}
