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

    std::string_view const s{"anagram"};
    std::string_view const t{"nagaram"};

    ankerl::nanobench::Bench()

        .title("Valid anagram")
        .relative(true)

        .run(
            NAMEOF_RAW(char_only::is_anagram).c_str(),
            [s, t] noexcept -> void {
                bool const volatile r{char_only::is_anagram(s, t)};

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(map_based::is_anagram<char>).c_str(),
            [s, t] -> void {
                bool const volatile r{map_based::is_anagram<char>(s, t)};

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(multiset_based::is_anagram<char>).c_str(),
            [s, t] -> void {
                bool const volatile r{multiset_based::is_anagram<char>(s, t)};

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
