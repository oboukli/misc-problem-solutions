// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/common/io.hpp"
#include "forfun/encode_and_decode_strings.hpp"

TEST_CASE(
    "Encode strings benchmarking", "[benchmark][encode_and_decode_strings]"
)
{
    using namespace forfun::encode_and_decode_strings;
    using std::string_view_literals::operator""sv;
    using ConstIter = std::array<std::string_view, 2>::const_iterator;
    using forfun::common::io::oblivion_stream;

    static constexpr std::array const tokens{
        // clang-format off
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"sv,
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"
        "abcd    ~~~~efghabcd    ~~~~efgh"sv,
        // clang-format off
    };
    static_assert(tokens.size() == 2U);
    static_assert(tokens[0].size() == 256U);
    static_assert(tokens[1].size() == 256U);

    forfun::common::io::oblivion_stream output_stream;

    ankerl::nanobench::Bench()

        .title("Encode strings")
        .relative(true)

        .run(
            NAMEOF_RAW(
                delimited::encode<ConstIter, ConstIter, decltype(output_stream)>
            )
                .c_str(),
            [&output_stream]() noexcept {
                delimited::encode(
                    tokens.cbegin(), tokens.cend(), output_stream
                );

                // ankerl::nanobench::doNotOptimizeAway(&output_stream.);
            }
        )

        ;
}

TEST_CASE(
    "Decode strings benchmarking", "[benchmark][encode_and_decode_strings]"
)
{
    using namespace forfun::encode_and_decode_strings;
    using std::string_view_literals::operator""sv;

    static constexpr std::string_view const encoded{
        // clang-format off
        "abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~"
        "~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ "
        "~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efgh"
        "abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~"
        "~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ "
        "~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efgh"
        " abcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~"
        "~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~"
        " ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efg"
        "habcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~"
        "~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~"
        " ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efghabcd~ ~ ~ ~ ~~~~~~~~efg"
        "h"sv
        // clang-format on
    };
    static_assert(encoded.size() == 769U);

    ankerl::nanobench::Bench()

        .title("Decode strings")
        .relative(true)

        .run(
            NAMEOF_RAW(delimited::decode).c_str(),
            []() noexcept {
                auto const volatile r{delimited::decode(encoded)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
