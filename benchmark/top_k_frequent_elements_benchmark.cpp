// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>

#include <catch2/catch_test_macros.hpp>

#include <nameof.hpp>

#include <nanobench.h>

#include "forfun/top_k_frequent_elements.hpp"

TEST_CASE(
    "Top K frequent elements benchmarking",
    "[benchmark][top_k_frequent_elements]"
)
{
    using namespace forfun::top_k_frequent_elements;

    using ContainerType = std::array<int, 16>;
    using Iter = ContainerType::iterator;

    static constexpr std::array const nums{
        61, 11, 8,  43, 29, 37, 29, 43, 11, 61, 29, 7,  8,  61, 7,  11,
        17, 13, 3,  29, 43, 29, 8,  8,  43, 29, 53, 19, 11, 23, 61, 7,
        43, 31, 43, 7,  11, 43, 43, 8,  59, 5,  8,  7,  17, 43, 7,  3,
        29, 2,  7,  11, 43, 43, 7,  8,  47, 53, 43, 29, 7,  7,  41, 43,
    };
    static_assert(nums.size() == 64UZ);

    ankerl::nanobench::Bench()

        .title("Top K frequent elements")
        .relative(true)

        .run(
            NAMEOF_RAW(bucket_sort_based::top_frequent<Iter, Iter>).c_str(),
            [] -> void {
                auto const volatile r{bucket_sort_based::top_frequent(
                    nums.begin(), nums.end(), 3U
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#if !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        .run(
            NAMEOF_RAW(bucket_sort_based_functional::top_frequent<Iter, Iter>)
                .c_str(),
            [] -> void {
                auto const volatile r{
                    bucket_sort_based_functional::top_frequent(
                        nums.begin(), nums.end(), 3U
                    )
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#endif // !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        .run(
            NAMEOF_RAW(priority_queue_based::top_frequent<Iter, Iter>).c_str(),
            [] -> void {
                auto const volatile r{priority_queue_based::top_frequent(
                    nums.cbegin(), nums.cend(), 3U
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#if !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        .run(
            NAMEOF_RAW(
                priority_queue_based_functional::top_frequent<Iter, Iter>
            )
                .c_str(),
            [] -> void {
                auto const volatile r{
                    priority_queue_based_functional::top_frequent(
                        nums.cbegin(), nums.cend(), 3U
                    )
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#endif // !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        .run(
            NAMEOF_RAW(sort_based::top_frequent<Iter, Iter>).c_str(),
            [] -> void {
                auto const volatile r{
                    sort_based::top_frequent(nums.cbegin(), nums.cend(), 3U)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#if !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        .run(
            NAMEOF_RAW(sort_based_functional_1::top_frequent<Iter, Iter>)
                .c_str(),
            [] -> void {
                auto const volatile r{sort_based_functional_1::top_frequent(
                    nums.cbegin(), nums.cend(), 3U
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#endif // !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

#if !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        .run(
            NAMEOF_RAW(sort_based_functional_2::top_frequent<Iter, Iter>)
                .c_str(),
            [] -> void {
                auto const volatile r{sort_based_functional_2::top_frequent(
                    nums.cbegin(), nums.cend(), 3U
                )};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#endif // !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

#if !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        .run(
            NAMEOF_RAW(max_heap_based::top_frequent<Iter, Iter>).c_str(),
            [] -> void {
                auto const volatile r{
                    max_heap_based::top_frequent(nums.cbegin(), nums.cend(), 3U)
                };
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

#endif // !defined(__GLIBCXX__) || __GLIBCXX__ >= 20250425

        ;
}
