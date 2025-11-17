// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <sstream>
#include <string>
#include <vector>

#include <fuzztest/fuzztest.h>

#include <gtest/gtest.h>

#include "forfun/encode_and_decode_strings.hpp"

namespace {

auto fuzz_encode_decode_empty_element_special_case() -> void
{
    std::vector<std::string> const tokens{{""}};
    std::ostringstream ss{};

    forfun::encode_and_decode_strings::delimited::encode(
        tokens.cbegin(), tokens.cend(), ss
    );

    auto const decoded{
        forfun::encode_and_decode_strings::delimited::decode(ss.view())
    };

    ASSERT_EQ(decoded, std::vector<std::string>{});
}

auto fuzz_encode_decode_general_case(std::vector<std::string> const& tokens)
    -> void
{
    std::ostringstream ss{};

    forfun::encode_and_decode_strings::delimited::encode(
        tokens.cbegin(), tokens.cend(), ss
    );

    auto const decoded{
        forfun::encode_and_decode_strings::delimited::decode(ss.view())
    };

    ASSERT_EQ(decoded, tokens);
}

auto ExceptSpecialCase()
{
    return ::fuzztest::Filter(
        [](std::vector<std::string> const& tokens) -> bool {
            return (tokens.size() != 1UZ) || (!tokens.front().empty());
        },
        ::fuzztest::Arbitrary<std::vector<std::string>>()
    );
}

} // namespace

FUZZ_TEST(
    encode_and_decode_strings, fuzz_encode_decode_empty_element_special_case
);

FUZZ_TEST(encode_and_decode_strings, fuzz_encode_decode_general_case)
    .WithDomains(ExceptSpecialCase());
