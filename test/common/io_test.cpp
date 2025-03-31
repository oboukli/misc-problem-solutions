// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <ostream>

#include <catch2/catch_test_macros.hpp>

#include "forfun/common/io.hpp"

TEST_CASE("Null stream buffer", "[null_streambuf]")
{
    SECTION("Absorb input")
    {
        forfun::common::io::null_streambuf buffer{};
        std::ostream os{&buffer};

        os << "Dummy";

        REQUIRE(os.good());
    }
}
