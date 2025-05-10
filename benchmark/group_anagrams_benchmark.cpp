// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/group_anagrams.hpp"

TEST_CASE("Group Anagrams benchmarking", "[benchmark][group_anagrams]")
{
    using namespace forfun::group_anagrams;

    std::array<std::string, 32UZ> const input{
        "abcd", "cadb",    "no",   "xyz",     "anagram", "silent",  "listen",
        "zyx",  "xzy",     "abcd", "cat",     "bcda",    "nagaram", "xyz",
        "yxz",  "xyz",     "",     "anagram", "dabc",    "cat",     "abcd",
        "",     "nagaram", "zxy",  "abcd",    "abcd",    "cdab",    "abcd",
        "xyz",  "abdc",    "on",   "abcd"
    };

    using CIter = decltype(input)::const_iterator;

    ankerl::nanobench::Bench()

        .title("Group Anagrams")
        .relative(true)

        .run(
            NAMEOF_RAW(group_anagrams<CIter, CIter>).c_str(),
            [&input]() {
                auto const volatile r{
                    group_anagrams(input.cbegin(), input.cend())
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
