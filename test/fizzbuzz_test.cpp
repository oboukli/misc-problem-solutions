// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <ios>
#include <limits>
#include <sstream>

#include <catch2/catch_case_sensitive.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>

#include "forfun/fizzbuzz.hpp"

TEST_CASE("Fizz buzz (namespace basic)", "[fizzbuzz]")
{
    using forfun::fizzbuzz::basic::fizzbuzz;

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

TEST_CASE("Fizz buzz (namespace optimized)", "[fizzbuzz]")
{
    using forfun::fizzbuzz::optimized::fizzbuzz;

    SECTION("From one to one inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            1,
            2,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("1", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to two inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            1,
            3,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("12", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to three inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            1,
            4,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("12Fizz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to five inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            1,
            6,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("12Fizz4Buzz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to six inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            1,
            7,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            10,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            11,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            12,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            16,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            17,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            18,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            21,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

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

        fizzbuzz(
            1,
            31,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617Fizz19BuzzFizz2"
                "223FizzBuzz26Fizz2829FizzBuzz",
                Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From minus fifteen to fifteen inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            -15,
            16,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals(
                "FizzBuzz-14-13Fizz-11BuzzFizz-8-7FizzBuzz-4Fizz-2-"
                "1FizzBuzz12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz",
                Catch::CaseSensitive::Yes
            )
        );
    }

    SECTION("From zero to one inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            0,
            2,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("FizzBuzz1", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From three to three inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            3,
            4,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("Fizz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From five to five inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            5,
            6,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("Buzz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From fifteen to fifteen inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            15,
            16,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("FizzBuzz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From seventeen to seventeen inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            17,
            18,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("17", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From min int to min int inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::min() + 1,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("-2147483648", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From max int to max int inclusive")
    {
        std::ostringstream stream;

        fizzbuzz(
            std::numeric_limits<int>::max() - 1,
            std::numeric_limits<int>::max(),
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(),
            Catch::Matchers::Equals("Fizz", Catch::CaseSensitive::Yes)
        );
    }

    SECTION("From one to zero")
    {
        std::ostringstream stream;

        fizzbuzz(
            1,
            0,
            [&stream](char const* const buffer, std::streamsize const size) {
                stream.write(buffer, size);
            }
        );

        REQUIRE_THAT(
            stream.str(), Catch::Matchers::Equals("", Catch::CaseSensitive::Yes)
        );
    }
}
