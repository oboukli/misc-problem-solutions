// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <format>
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
    using ElementAllocatorFactory
        = ElementInPlaceAllocatorFactory<ElementType, num_elements>;
    using SubsetAllocatorFactory = SubsetInPlaceAllocatorFactory<
        ElementType,
        ElementAllocatorFactory::allocator_type,
        num_elements>;

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

        .run(
            std::format(
                "{} preallocated",
                // clang-format off
                NAMEOF_RAW(
                    recursive::explode_subsets<
                        ConstIter,
                        ConstIter,
                        ElementAllocatorFactory,
                        SubsetAllocatorFactory>
                )
                .c_str()
                // clang-format on
            ),
            [&elements] noexcept -> void {
                SubsetAllocatorFactory const subset_allocator_factory{};
                ElementAllocatorFactory const element_allocator_factory{};

                auto const volatile r{recursive::explode_subsets(
                    elements.cbegin(),
                    elements.cend(),
                    subset_allocator_factory.allocator(),
                    element_allocator_factory.allocator()
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
