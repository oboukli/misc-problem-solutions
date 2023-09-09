// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "forfun/fizzbuzz.hpp"

TEST_CASE("fizzbuzz")
{
    SECTION("Numbers other than three and five are concatenated as-is")
    {
        REQUIRE_THAT(
            fizzbuzz(1),
            Catch::Matchers::Equals("1", Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(2),
            Catch::Matchers::Equals("12", Catch::CaseSensitive::Yes));
    }

    SECTION("Multiples of three are concatenated as Fizz")
    {
        REQUIRE_THAT(
            fizzbuzz(3),
            Catch::Matchers::Equals("12Fizz", Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(6),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz", Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(9),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78Fizz", Catch::CaseSensitive::Yes));
    }

    SECTION("Multiples of five are concatenated as Buzz")
    {
        REQUIRE_THAT(
            fizzbuzz(5),
            Catch::Matchers::Equals("12Fizz4Buzz", Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(10),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz", Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(20),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617Fizz19Buzz",
                Catch::CaseSensitive::Yes));
    }

    SECTION("Multiples of both three and five are concatenated as FizzBuzz")
    {
        REQUIRE_THAT(
            fizzbuzz(15),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz",
                Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(16),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz16",
                Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(30),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617Fizz19BuzzFizz2"
                "223FizzBuzz26Fizz2829FizzBuzz",
                Catch::CaseSensitive::Yes));
    }

    SECTION("Prime number input is computed correctly")
    {
        REQUIRE_THAT(
            fizzbuzz(11),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11", Catch::CaseSensitive::Yes));

        REQUIRE_THAT(
            fizzbuzz(17),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617",
                Catch::CaseSensitive::Yes));
    }
}
