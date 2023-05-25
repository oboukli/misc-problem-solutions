// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://imranontech.com/2007/01/24/using-fizzbuzz-to-find-developers-who-grok-coding/
///
/// Original problem text:
/// Write a program that prints the numbers from 1 to 100. But for multiples of
/// three print "Fizz" instead of the number and for the multiples of five
/// print "Buzz". For numbers which are multiples of both three and five print
/// "FizzBuzz".

#include <cassert>
#include <sstream>
#include <string>

std::string fizzbuzz(int const n) noexcept {
    std::ostringstream buffer;
    for (int i{1}; i <= n; ++i) {
        bool f{true};

        if (i % 3 == 0) {
            buffer << "Fizz";
            f = false;
        }

        if (i % 5 == 0) {
            buffer << "Buzz";
            continue;
        }

        if (f) {
            buffer << i;
        }
    }

    return buffer.str();
}

int main() {
    {
        auto actual = fizzbuzz(1);
        assert(actual == "1");
    }

    {
        auto actual = fizzbuzz(2);
        assert(actual == "12");
    }

    {
        auto actual = fizzbuzz(3);
        assert(actual == "12Fizz");
    }

    {
        auto actual = fizzbuzz(4);
        assert(actual == "12Fizz4");
    }

    {
        auto actual = fizzbuzz(5);
        assert(actual == "12Fizz4Buzz");
    }

    {
        auto actual = fizzbuzz(6);
        assert(actual == "12Fizz4BuzzFizz");
    }

    {
        auto actual = fizzbuzz(15);
        assert(actual == "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz");
    }

    {
        auto actual = fizzbuzz(16);
        assert(actual == "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz16");
    }

    {
        auto actual = fizzbuzz(17);
        assert(actual == "12Fizz4BuzzFizz78FizzBuzz11Fizz1314FizzBuzz1617");
    }

    return 0;
}
