// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <format>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include "forfun/lru_cache.hpp"

namespace {

template <forfun::lrucache::concepts::lru_cache T>
auto wrapper(std::size_t const capacity) noexcept -> int
{
    T cache(capacity);

    int x{0};
    for (std::size_t i{0}; i < capacity; ++i)
    {
        cache.put(i, x);
        ++x;
    }

    int val{cache.get(1)};

    val = cache.get(2);

    val = cache.get(3);

    cache.put(capacity + 1, 2'946'901);

    val = cache.get(1);

    val = cache.get(4);

    val = cache.get(2);

    cache.put(5, 5);

    val = cache.get(3);

    for (std::size_t i{0}; i < capacity; ++i)
    {
        val = cache.get(i);
    }

    return val;
}

} // namespace

TEST_CASE("LRU cache benchmarking", "[benchmark][lrucache]")
{
    using namespace forfun::lrucache;

    SECTION("small")
    {
        static constexpr int const lrucache_capacity{32};

        ankerl::nanobench::Bench()

            .title(
                std::format("LRU cache with {} cache items", lrucache_capacity)
            )
            .relative(true)

            .run(
                "stl::LRUCache",
                []() {
                    int val{wrapper<stl::LRUCache>(lrucache_capacity)};

                    ankerl::nanobench::doNotOptimizeAway(val);
                }
            )

            .run(
                "naive::LRUCache",
                []() {
                    int val{wrapper<naive::LRUCache>(lrucache_capacity)};

                    ankerl::nanobench::doNotOptimizeAway(val);
                }
            )

            ;
    }

    SECTION("large")
    {
        static constexpr int const lrucache_capacity{128};

        ankerl::nanobench::Bench()

            .title(
                std::format("LRU cache with {} cache items", lrucache_capacity)
            )
            .relative(true)

            .run(
                "stl::LRUCache",
                []() {
                    int val{wrapper<stl::LRUCache>(lrucache_capacity)};

                    ankerl::nanobench::doNotOptimizeAway(val);
                }
            )

            .run(
                "naive::LRUCache",
                []() {
                    int val{wrapper<naive::LRUCache>(lrucache_capacity)};

                    ankerl::nanobench::doNotOptimizeAway(val);
                }
            )

            ;
    }
}
