// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/math/math.hpp"

TEST_CASE("Integer division ceiling", "[math]")
{
    STATIC_REQUIRE(forfun::math::alternative::div_ceil(1, 1) == 1);

    STATIC_REQUIRE(forfun::math::alternative::div_ceil(2, 3) == 1);

    STATIC_REQUIRE(forfun::math::alternative::div_ceil(3, 2) == 2);
}

TEST_CASE("Catalan number", "[math]")
{
    STATIC_REQUIRE(forfun::math::lookup::catalan(5) == 42UZ);
}
