// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdint>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "forfun/common.hpp"

TEST_CASE("Concept addition_unpromoted", "[common]")
{
    using forfun::common::concepts::addition_unpromoted;

    SECTION("Positive")
    {
        STATIC_REQUIRE(addition_unpromoted<int>);
        STATIC_REQUIRE(addition_unpromoted<unsigned int>);
        STATIC_REQUIRE(addition_unpromoted<std::int32_t>);
        STATIC_REQUIRE(addition_unpromoted<std::uint32_t>);
        STATIC_REQUIRE(addition_unpromoted<std::size_t>);
        STATIC_REQUIRE(addition_unpromoted<std::int64_t>);
        STATIC_REQUIRE(addition_unpromoted<std::uint64_t>);
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(addition_unpromoted<char>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<short>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<unsigned short>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<std::int8_t>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<std::uint8_t>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<std::int16_t>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<std::uint16_t>);

        STATIC_REQUIRE_FALSE(addition_unpromoted<float>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<double>);

        STATIC_REQUIRE_FALSE(addition_unpromoted<std::string>);
    }
}
