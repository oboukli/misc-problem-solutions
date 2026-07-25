// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <nameof.hpp>

#include <nanobench.h>

#include "forfun/valid_anagram.hpp"

TEST_CASE("Valid anagram benchmarking", "[benchmark][valid_anagram]")
{
    using namespace forfun::valid_anagram;

    std::string_view const str_a{"anagram"};
    std::string_view const str_b{"nagaram"};

    ankerl::nanobench::Bench()

        .title("Valid anagram")
        .relative(true)

        .run(
            NAMEOF_RAW(char_only::is_anagram).c_str(),
            [str_a, str_b] noexcept -> void {
                bool const volatile r{char_only::is_anagram(str_a, str_b)};

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(map_based::is_anagram<char>).c_str(),
            [str_a, str_b] -> void {
                bool const volatile r{
                    map_based::is_anagram<char>(str_a, str_b)
                };

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(multiset_based::is_anagram<char>).c_str(),
            [str_a, str_b] -> void {
                bool const volatile r{
                    multiset_based::is_anagram<char>(str_a, str_b)
                };

                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
