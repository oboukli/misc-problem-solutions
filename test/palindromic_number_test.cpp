// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include "forfun/palindromic_number.hpp"

TEMPLATE_TEST_CASE_SIG(
    "palindromic_number", "[palindromic_number]", ((auto sut), sut),
    (forfun::palindromic_number::fast::is_palindrome<int>),
    (forfun::palindromic_number::stl::is_palindrome)) {
    SECTION("Palindromic numbers") {
        GIVEN("a palindromic number") {
            auto const [palindromic_number]{GENERATE(table<int>({
                {0},
                {1},
                {11},
                {121},
                {212},
                {333},
                {4444},
                {14341},
                {143341},
                {4268624},
                {1234554321},
            }))};

            CAPTURE(palindromic_number);

            WHEN("is_palindrome checked") {
                THEN("true") {
                    REQUIRE(sut(palindromic_number));
                }
            }
        }
    }

    SECTION("Non-palindromic numbers") {
        GIVEN("a non-palindromic number") {
            auto const [non_palindromic_number]{GENERATE(table<int>({
                {std::numeric_limits<int>::min()},
                {-1},
                {-32},
                {12},
                {112},
                {1121},
                {12325},
                {4268604},
                {std::numeric_limits<int>::max()},
            }))};

            CAPTURE(non_palindromic_number);

            WHEN("is_palindrome checked") {
                THEN("false") {
                    REQUIRE_FALSE(sut(non_palindromic_number));
                }
            }
        }
    }
}

TEST_CASE("palindromic_number_static", "[palindromic_number][static]") {
    SECTION("Palindromic integrals") {
        STATIC_REQUIRE(
            forfun::palindromic_number::fast::is_palindrome(char{33}));

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(7));

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(1881));

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(55l));

        STATIC_REQUIRE(forfun::palindromic_number::fast::is_palindrome(33ull));
    }

    SECTION("Non-palindromic integrals") {
        STATIC_REQUIRE_FALSE(
            forfun::palindromic_number::fast::is_palindrome(-1));

        STATIC_REQUIRE_FALSE(
            forfun::palindromic_number::fast::is_palindrome(char{65}));
    }
}
