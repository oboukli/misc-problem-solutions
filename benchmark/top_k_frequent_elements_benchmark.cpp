// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/top_k_frequent_elements.hpp"

TEST_CASE(
    "Top K frequent elements benchmarking",
    "[benchmark][top_k_frequent_elements]"
)
{
    using namespace forfun::top_k_frequent_elements;

    using ContainerType = std::array<int, 16>;
    using Iter = ContainerType::iterator;

    ankerl::nanobench::Bench()

        .title("Top K frequent elements")
        .relative(true)

        .run(
            NAMEOF_RAW(bucket_sort_based::top_frequent<Iter, Iter>).c_str(),
            []() {
                std::array nums{
                    5, 3, 3, 8, 8, 8, 11, 11, 11, 11, 7, 7, 7, 7, 7, 2, 2
                };

                auto const volatile r{bucket_sort_based::top_frequent(
                    nums.begin(), nums.end(), 3U
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(bucket_sort_based_functional::top_frequent<Iter, Iter>)
                .c_str(),
            []() {
                std::array nums{
                    5, 3, 3, 8, 8, 8, 11, 11, 11, 11, 7, 7, 7, 7, 7, 2, 2
                };

                auto const volatile r{
                    bucket_sort_based_functional::top_frequent(
                        nums.begin(), nums.end(), 3U
                    )
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(priority_queue_based::top_frequent<Iter, Iter>).c_str(),
            []() {
                static constexpr std::array const nums{
                    5, 3, 3, 8, 8, 8, 11, 11, 11, 11, 7, 7, 7, 7, 7, 2, 2
                };

                auto const volatile r{priority_queue_based::top_frequent(
                    nums.cbegin(), nums.cend(), 3U
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(
                priority_queue_based_functional::top_frequent<Iter, Iter>
            )
                .c_str(),
            []() {
                static constexpr std::array const nums{
                    5, 3, 3, 8, 8, 8, 11, 11, 11, 11, 7, 7, 7, 7, 7, 2, 2
                };

                auto const volatile r{
                    priority_queue_based_functional::top_frequent(
                        nums.cbegin(), nums.cend(), 3U
                    )
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(unordered_map_based::top_frequent<Iter, Iter>).c_str(),
            []() {
                static constexpr std::array const nums{
                    5, 3, 3, 8, 8, 8, 11, 11, 11, 11, 7, 7, 7, 7, 7, 2, 2
                };

                auto const volatile r{unordered_map_based::top_frequent(
                    nums.cbegin(), nums.cend(), 3U
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        .run(
            NAMEOF_RAW(unordered_map_based_functional::top_frequent<Iter, Iter>)
                .c_str(),
            []() {
                static constexpr std::array const nums{
                    5, 3, 3, 8, 8, 8, 11, 11, 11, 11, 7, 7, 7, 7, 7, 2, 2
                };

                auto const volatile r{
                    unordered_map_based_functional::top_frequent(
                        nums.cbegin(), nums.cend(), 3U
                    )
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
