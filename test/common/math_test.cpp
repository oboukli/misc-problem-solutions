// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <limits>

#include <catch2/catch_test_macros.hpp>

#include "forfun/common/math.hpp"

TEST_CASE("Integer division ceiling", "[math]")
{
    REQUIRE(forfun::common::math::div_ceil(1, 1) == 1);

    REQUIRE(forfun::common::math::div_ceil(2, 2) == 1);

    REQUIRE(
        forfun::common::math::div_ceil(
            std::numeric_limits<int>::max(), std::numeric_limits<int>::max()
        )
        == 1
    );

    REQUIRE(forfun::common::math::div_ceil(1, 3) == 1);

    REQUIRE(forfun::common::math::div_ceil(2, 3) == 1);

    REQUIRE(forfun::common::math::div_ceil(3, 2) == 2);

    REQUIRE(
        forfun::common::math::div_ceil(
            std::numeric_limits<int>::max(), std::numeric_limits<int>::max() - 1
        )
        == 2
    );

    REQUIRE(forfun::common::math::div_ceil(3, 1) == 3);
}
