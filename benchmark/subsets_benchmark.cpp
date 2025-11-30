// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/subsets.hpp"

TEST_CASE("Subsets benchmarking", "[benchmark][subsets]")
{
    using namespace forfun::subsets;

    static constexpr std::size_t const num_elements{4};

    using ElementType = int;
    using ConstIter = std::vector<ElementType>::const_iterator;
    using ElementDefaultAllocator = std::vector<ElementType>::allocator_type;
    using SubsetDefaultAllocator = std::vector<
        std::vector<ElementType, ElementDefaultAllocator>>::allocator_type;

    std::vector const elements{23, 29, 31, 37};

    ankerl::nanobench::Bench()

        .title("Subsets")
        .relative(true)

        .run(
            // clang-format off
            NAMEOF_RAW(
                recursive::explode_subsets<
                    ConstIter,
                    ConstIter,
                    ElementDefaultAllocator,
                    SubsetDefaultAllocator>
            )
            .c_str(),
            // clang-format on
            [&elements] -> void {
                auto const volatile r{recursive::explode_subsets(
                    elements.cbegin(), elements.cend()
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
