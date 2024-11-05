// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <sstream>

#include <catch2/catch_case_sensitive.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "forfun/fizzbuzz.hpp"

TEST_CASE("Fizz buzz", "[fizzbuzz]")
{
    using forfun::fizzbuzz::fizzbuzz;

    SECTION("From one to one inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(1, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("1", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to two inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(2, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("12", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to three inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(3, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("12Fizz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to five inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(5, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("12Fizz4Buzz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to six inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(6, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz", Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to nine inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(9, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78Fizz", Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to ten inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(10, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz", Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to eleven inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(11, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11", Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to fifteen inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(15, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz",
                Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to sixteen inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(16, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz16",
                Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to seventeen inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(17, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617",
                Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to twenty inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(20, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617Fizz19Buzz",
                Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From one to thirty inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(30, stream);

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617Fizz19BuzzFizz2"
                "223FizzBuzz26Fizz2829FizzBuzz",
                Catch::CaseSensitive::Yes
            )
        );
    }
}
