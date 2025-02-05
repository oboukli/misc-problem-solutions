// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/palindromic_number.hpp"

TEST_CASE("Palindromic number (static)", "[palindromic_number]")
{
    SECTION("Palindromic integrals")
    {
        STATIC_REQUIRE(
            forfun::palindromic_number::fast::is_palindrome(char{33})
        );

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(7));

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(1881));

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(55L));

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(33ULL));
    }

    SECTION("Non-palindromic integrals")
    {
        STATIC_REQUIRE_FALSE(
            forfun::palindromic_number::fast::is_palindrome(-1)
        );

        STATIC_REQUIRE_FALSE(
            forfun::palindromic_number::fast::is_palindrome(char{65})
        );
    }
}
