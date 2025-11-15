// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/subsets.hpp"

TEST_CASE("Subsets benchmarking", "[benchmark][subsets]")
{
    using namespace forfun::subsets;

    using SubsetAllocator = std::vector<int>::allocator_type;
    using SetAllocator
        = std::vector<std::vector<int, SubsetAllocator>>::allocator_type;

    std::vector const elements{23, 29, 31, 37};

    ankerl::nanobench::Bench()

        .title("Subsets")
        .relative(true)

        .run(
            NAMEOF_RAW(
                recursive::explode_subsets<SubsetAllocator, SetAllocator>
            )
                .c_str(),
            [&elements] noexcept -> void {
                auto const volatile r{recursive::explode_subsets(elements)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
