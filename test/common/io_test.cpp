// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_test_macros.hpp>

#include "forfun/common/io.hpp"

TEST_CASE("Oblivion Stream", "[oblivion_stream]")
{
    using forfun::common::io::oblivion_stream;

    SECTION("")
    {
        oblivion_stream os{};

        os << "Dummy";

        REQUIRE(os.good());
    }
}
