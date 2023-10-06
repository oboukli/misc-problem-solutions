// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

#include <nanobench.h>

#include <nameof.hpp>

#include <fmt/format.h>

#include "forfun/lru_cache.hpp"

template <typename T>
std::enable_if_t<std::is_base_of_v<forfun::lrucache::LRUCacheBase, T>, void>
test(std::size_t const capacity)
{
    int volatile val{};
    T cache(capacity);

    int x{0};
    for (std::size_t i{0}; i < capacity; ++i)
    {
        cache.put(i, x);
        ++x;
    }

    val = cache.get(1);

    val = cache.get(2);

    val = cache.get(3);

    cache.put(capacity + 1, 2946901);

    val = cache.get(1);

    val = cache.get(4);

    val = cache.get(2);

    cache.put(5, 5);

    val = cache.get(3);

    for (std::size_t i{0}; i < capacity; ++i)
    {
        val = cache.get(i);
    }
}

TEST_CASE("forfun::lrucache benchmarking", "[benchmark][lrucache]")
{
    SECTION("small")
    {
        static constexpr int const lrucache_capacity{32};

        ankerl::nanobench::Bench()

            .title(
                fmt::format("LRU Cache with {} cache items", lrucache_capacity))

            .run(
                NAMEOF_FULL_TYPE(forfun::lrucache::stl::LRUCache).data(),
                []() {
                    test<forfun::lrucache::stl::LRUCache>(lrucache_capacity);
                })

            .run(
                NAMEOF_FULL_TYPE(forfun::lrucache::naive::LRUCache).data(),
                []() {
                    test<forfun::lrucache::naive::LRUCache>(lrucache_capacity);
                })

            ;
    }

    SECTION("large")
    {
        static constexpr int const lrucache_capacity{128};

        ankerl::nanobench::Bench()

            .title(
                fmt::format("LRU Cache with {} cache items", lrucache_capacity))

            .run(
                NAMEOF_FULL_TYPE(forfun::lrucache::stl::LRUCache).data(),
                []() {
                    test<forfun::lrucache::stl::LRUCache>(lrucache_capacity);
                })

            .run(
                NAMEOF_FULL_TYPE(forfun::lrucache::naive::LRUCache).data(),
                []() {
                    test<forfun::lrucache::naive::LRUCache>(lrucache_capacity);
                })

            ;
    }
}
