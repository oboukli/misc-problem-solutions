// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/fizzbuzz.hpp"

#include <cassert>

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
