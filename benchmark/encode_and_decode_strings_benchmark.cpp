// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <ostream>
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

    forfun::common::io::null_streambuf buffer{};
    std::ostream output_stream{&buffer};

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
        // clang-format on
    };
    static_assert(tokens.size() == 2UZ);
    static_assert(tokens[0].size() == 256UZ);
    static_assert(tokens[1].size() == 256UZ);

    ankerl::nanobench::Bench()

        .title("Encode strings")
        .relative(true)

        .run(
            NAMEOF_RAW(delimited::encode<ConstIter, ConstIter, std::ostream>)
                .c_str(),
            [&output_stream]() {
                delimited::encode(
                    tokens.cbegin(), tokens.cend(), output_stream
                );
            }
        )

        ;
}

TEST_CASE(
    "Decode strings benchmarking", "[benchmark][encode_and_decode_strings]"
)
{
    using namespace forfun::encode_and_decode_strings;

    using CharT = std::string_view::value_type;
    using Traits = std::string_view::traits_type;

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
        "h"
        // clang-format on
    };
    static_assert(encoded.size() == 769UZ);

    ankerl::nanobench::Bench()

        .title("Decode strings")
        .relative(true)

        .run(
            NAMEOF_RAW(delimited::decode<CharT, Traits>).c_str(),
            []() {
                auto const volatile r{delimited::decode(encoded)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
