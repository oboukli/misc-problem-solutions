// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://imranontech.com/2007/01/24/using-fizzbuzz-to-find-developers-who-grok-coding/
/// https://en.wikipedia.org/wiki/Fizz_buzz
///
/// Original problem text:
/// Write a program that prints the numbers from 1 to 100. But for multiples of
/// three print "Fizz" instead of the number and for the multiples of five
/// print "Buzz". For numbers which are multiples of both three and five print
/// "FizzBuzz".

#ifndef FORFUN_FIZZBUZZ_HPP_
#define FORFUN_FIZZBUZZ_HPP_

#include <ostream>

namespace forfun::fizzbuzz {

auto fizzbuzz(int n, std::ostream& stream) -> void;

} // namespace forfun::fizzbuzz

#endif // FORFUN_FIZZBUZZ_HPP_
