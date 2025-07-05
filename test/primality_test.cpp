// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include <forfun/primality.hpp>

TEST_CASE("Primality", "[primality]")
{
    using forfun::primality::is_prime;

    SECTION("Even non primes")
    {
        REQUIRE_FALSE(is_prime(0U));
        REQUIRE_FALSE(is_prime(6U));
        REQUIRE_FALSE(is_prime(60U));
        REQUIRE_FALSE(is_prime(128U));
        REQUIRE_FALSE(is_prime(1000U));
    }

    SECTION("Odd non primes")
    {
        REQUIRE_FALSE(is_prime(1U));
        REQUIRE_FALSE(is_prime(9U));
        REQUIRE_FALSE(is_prime(33U));
        REQUIRE_FALSE(is_prime(111U));
        REQUIRE_FALSE(is_prime(1001U));
    }

    SECTION("Primes")
    {
        REQUIRE(is_prime(2U));
        REQUIRE(is_prime(3U));
        REQUIRE(is_prime(11U));
        REQUIRE(is_prime(197U));
        REQUIRE(is_prime(1009U));
        REQUIRE(is_prime(19391U));
        REQUIRE(is_prime(181081U));
    }

    SECTION("Largest prime less than the limit of std::uint32_t")
    {
        // https://en.wikipedia.org/wiki/Double_Mersenne_number
        static constexpr std::uint32_t const max_uint32_prime{2'147'483'647U};
        REQUIRE(is_prime(max_uint32_prime));
    }
}
