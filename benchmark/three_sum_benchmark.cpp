// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/three_sum.hpp"

TEST_CASE("Three sum benchmarking", "[benchmark][three_sum]")
{
    using CIter = std::vector<int>::const_iterator;

    SECTION("Presorted input")
    {
        using namespace forfun::three_sum::presorted;
        using namespace forfun::three_sum::non_presorted;

        std::vector const nums{
            // clang-format off
            -10, -10, -10, -10, -7, -6, -5, -2,
            0,   2,   3,   3,   3,  4,  4,  5,
            5,   5,   6,   6,   6,  7,  7,  10,
            11,  15,  17,  17,  20, 20, 21, 30,
            // clang-format on
        };

        ankerl::nanobench::Bench()

            .title("Three sum (presorted input)")
            .relative(true)

            .run(
                NAMEOF_RAW(set_based::three_sum<CIter, CIter>).c_str(),
                [&nums] {
                    auto const volatile r{
                        set_based::three_sum(nums.cbegin(), nums.cend())
                    };
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            .run(
                NAMEOF_RAW(two_pointer::three_sum<CIter, CIter>).c_str(),
                [&nums] {
                    auto const volatile r{
                        two_pointer::three_sum(nums.cbegin(), nums.cend())
                    };
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            .run(
                NAMEOF_RAW(brute_force::three_sum<CIter, CIter>).c_str(),
                [&nums] {
                    auto const volatile r{
                        brute_force::three_sum(nums.cbegin(), nums.cend())
                    };
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            .run(
                NAMEOF_RAW(set_map_based::three_sum<CIter, CIter>).c_str(),
                [&nums] {
                    auto const volatile r{
                        set_map_based::three_sum(nums.cbegin(), nums.cend())
                    };
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            ;
    }

    SECTION("Unsorted")
    {
        using namespace forfun::three_sum::non_presorted;

        std::vector const nums{
            // clang-format off
            0,   15,  21, 5,   3, 7,  -7,  6,
            -10, -5,  4,  30,  2, 11, 3,   20,
            10,  20,  5,  -10, 6, 3,  -10, -2,
            4,   -10, 17, -6,  5, 17, 6,   7,
            // clang-format on
        };

        ankerl::nanobench::Bench()

            .title("Three sum")
            .relative(true)

            .run(
                NAMEOF_RAW(set_based::three_sum<CIter, CIter>).c_str(),
                [&nums] {
                    auto const volatile r{
                        set_based::three_sum(nums.cbegin(), nums.cend())
                    };
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            .run(
                NAMEOF_RAW(brute_force::three_sum<CIter, CIter>).c_str(),
                [&nums] {
                    auto const volatile r{
                        brute_force::three_sum(nums.cbegin(), nums.cend())
                    };
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            ;
    }

    SECTION("With std::sort scaffolds")
    {
        using namespace forfun::three_sum;

        ankerl::nanobench::Bench()

            .title("Three sum (with std::sort scaffolds)")
            .relative(true)

            .run(
                NAMEOF_RAW(non_presorted::set_based::three_sum<CIter, CIter>)
                    .c_str(),
                [] {
                    std::vector const nums{
                        // clang-format off
                        0,   15,  21, 5,   3, 7,  -7,  6,
                        -10, -5,  4,  30,  2, 11, 3,   20,
                        10,  20,  5,  -10, 6, 3,  -10, -2,
                        4,   -10, 17, -6,  5, 17, 6,   7,
                        // clang-format on
                    };

                    auto const volatile r{non_presorted::set_based::three_sum(
                        nums.cbegin(), nums.cend()
                    )};
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            .run(
                NAMEOF_RAW(presorted::two_pointer::three_sum<CIter, CIter>)
                    .c_str(),
                [] {
                    std::vector nums{
                        // clang-format off
                        0,   15,  21, 5,   3, 7,  -7,  6,
                        -10, -5,  4,  30,  2, 11, 3,   20,
                        10,  20,  5,  -10, 6, 3,  -10, -2,
                        4,   -10, 17, -6,  5, 17, 6,   7,
                        // clang-format on
                    };

                    std::ranges::sort(nums);

                    auto const volatile r{presorted::two_pointer::three_sum(
                        nums.cbegin(), nums.cend()
                    )};
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            .run(
                NAMEOF_RAW(non_presorted::brute_force::three_sum<CIter, CIter>)
                    .c_str(),
                [] {
                    std::vector const nums{
                        // clang-format off
                        0,   15,  21, 5,   3, 7,  -7,  6,
                        -10, -5,  4,  30,  2, 11, 3,   20,
                        10,  20,  5,  -10, 6, 3,  -10, -2,
                        4,   -10, 17, -6,  5, 17, 6,   7,
                        // clang-format on
                    };

                    auto const volatile r{non_presorted::brute_force::three_sum(
                        nums.cbegin(), nums.cend()
                    )};
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            .run(
                NAMEOF_RAW(presorted::set_map_based::three_sum<CIter, CIter>)
                    .c_str(),
                [] {
                    std::vector nums{
                        // clang-format off
                        0,   15,  21, 5,   3, 7,  -7,  6,
                        -10, -5,  4,  30,  2, 11, 3,   20,
                        10,  20,  5,  -10, 6, 3,  -10, -2,
                        4,   -10, 17, -6,  5, 17, 6,   7,
                        // clang-format on
                    };

                    std::ranges::sort(nums);

                    auto const volatile r{presorted::set_map_based::three_sum(
                        nums.cbegin(), nums.cend()
                    )};
                    ankerl::nanobench::doNotOptimizeAway(&r);
                }
            )

            ;
    }
}
