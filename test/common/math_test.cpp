// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <limits>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/common/math.hpp"

TEMPLATE_TEST_CASE_SIG(
    "Integer division ceiling",
    "[math]",
    (auto div_ceil, div_ceil),
    forfun::common::math::alternative::div_ceil,
    forfun::common::math::core::div_ceil
)
{
    REQUIRE(div_ceil(1, 1) == 1);

    REQUIRE(div_ceil(2, 2) == 1);

    REQUIRE(
        div_ceil(
            std::numeric_limits<int>::max(), std::numeric_limits<int>::max()
        )
        == 1
    );

    REQUIRE(div_ceil(1, 3) == 1);

    REQUIRE(div_ceil(2, 3) == 1);

    REQUIRE(div_ceil(3, 2) == 2);

    REQUIRE(
        div_ceil(
            std::numeric_limits<int>::max(), std::numeric_limits<int>::max() - 1
        )
        == 2
    );

    REQUIRE(div_ceil(3, 1) == 3);
}
