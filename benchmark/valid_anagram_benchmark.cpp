// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/valid_anagram.hpp"

TEST_CASE("Valid anagram benchmarking", "[benchmark][valid_anagram]")
{
    using namespace forfun::valid_anagram;
    using std::string_view_literals::operator""sv;

    ankerl::nanobench::Bench()

        .title("Valid anagram")
        .relative(true)

        .run(
            NAMEOF_RAW(char_only::is_anagram).c_str(),
            []() noexcept {
                bool const r{char_only::is_anagram("anagram"sv, "nagaram"sv)};

                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        .run(
            NAMEOF_RAW(generic::is_anagram<char>).c_str(),
            []() noexcept(false) {
                bool const r{generic::is_anagram<char>("anagram"sv, "nagaram"sv)
                };

                ankerl::nanobench::doNotOptimizeAway(r);
            }
        )

        ;
}
