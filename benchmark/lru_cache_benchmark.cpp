// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_test_macros.hpp>

#include <fmt/core.h>

#include <nanobench.h>

#include <nameof.hpp>

#include "forfun/lru_cache.hpp"

namespace {

template <forfun::lrucache::concepts::lru_cache T>
auto test(std::size_t const capacity) noexcept -> void
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
}

} // namespace

TEST_CASE("forfun::lrucache benchmarking", "[benchmark][lrucache]")
{
    using namespace forfun::lrucache;

    SECTION("small")
    {
        static constexpr int const lrucache_capacity{32};

        ankerl::nanobench::Bench()

            .title(
                fmt::format("LRU Cache with {} cache items", lrucache_capacity))
            .relative(true)

            .run(
                NAMEOF_TYPE(stl::LRUCache).data(),
                []() { test<stl::LRUCache>(lrucache_capacity); })

            .run(
                NAMEOF_TYPE(naive::LRUCache).data(),
                []() { test<naive::LRUCache>(lrucache_capacity); })

            ;
    }

    SECTION("large")
    {
        static constexpr int const lrucache_capacity{128};

        ankerl::nanobench::Bench()

            .title(
                fmt::format("LRU Cache with {} cache items", lrucache_capacity))
            .relative(true)

            .run(
                NAMEOF_TYPE(stl::LRUCache).data(),
                []() { test<stl::LRUCache>(lrucache_capacity); })

            .run(
                NAMEOF_TYPE(naive::LRUCache).data(),
                []() { test<naive::LRUCache>(lrucache_capacity); })

            ;
    }
}
