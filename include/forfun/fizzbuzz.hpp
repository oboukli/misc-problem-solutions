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

#include <array>
#include <cassert>
#include <charconv>
#include <concepts>
#include <cstddef>
#include <ios>
#include <limits>
#include <ostream>
#include <string_view>

#ifndef NDEBUG
#include <system_error>
#endif

namespace forfun::fizzbuzz {

namespace basic {

auto fizzbuzz(int n, std::ostream& stream) -> void;

} // namespace basic

namespace optimized {

/// Support values of int up to std::numeric_limits<int>::max() - 1 inclusive.
template <typename BinaryFunc>
    requires std::invocable<BinaryFunc, char const*, std::streamsize>
auto
fizzbuzz(int start, int const last, BinaryFunc write) noexcept(noexcept(write))
    -> void
{
    static constexpr int const fizz_divider{3};
    static constexpr int const buzz_divider{5};
    static constexpr std::string_view const fizz{"Fizz"};
    static constexpr std::string_view const buzz{"Buzz"};

    for (; start < last; ++start)
    {
        bool is_numeric{true};

        if ((start % fizz_divider) == 0)
        {
            write(fizz.data(), fizz.size());

            is_numeric = false;
        }

        if ((start % buzz_divider) == 0)
        {
            write(buzz.data(), buzz.size());
        }
        else if (is_numeric)
        {
            // Create char buffer sufficient for int's maximum number of decimal
            // digits and one sign.
            static constexpr std::size_t const buffer_size{
                std::numeric_limits<decltype(start)>::digits10 + 2
            };
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
            std::array<char, buffer_size> buffer /*[[indeterminate]]*/;

            std::to_chars_result const result{
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                std::to_chars(buffer.data(), buffer.data() + buffer_size, start)
            };

            assert(result.ec == std::errc{});

            write(buffer.data(), result.ptr - buffer.data());
        }
    }
}

} // namespace optimized

} // namespace forfun::fizzbuzz

#endif // FORFUN_FIZZBUZZ_HPP_
