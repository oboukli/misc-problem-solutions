// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

#include "forfun/common/limits.hpp"

TEST_CASE("Domain size", "[limits]")
{
    STATIC_REQUIRE(forfun::common::limits::domain_size<signed char>() == 256UZ);

    STATIC_REQUIRE(
        forfun::common::limits::domain_size<unsigned char>() == 256UZ
    );

    STATIC_REQUIRE(forfun::common::limits::domain_size<char8_t>() == 256UZ);

    STATIC_REQUIRE(
        forfun::common::limits::domain_size<std::int16_t>() == 65'536UZ
    );

    STATIC_REQUIRE(
        forfun::common::limits::domain_size<std::uint16_t>() == 65'536UZ
    );
}
