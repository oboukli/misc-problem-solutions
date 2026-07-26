// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/lru_cache.hpp"

TEMPLATE_TEST_CASE(
    "LRU cache",
    "[lru_cache]",
    forfun::lrucache::naive::LRUCache,
    forfun::lrucache::stl::LRUCache
)
{
    using CacheType = TestType;

    static_assert(forfun::lrucache::concepts::lru_cache<CacheType>);

    int volatile val{};

    SECTION("Test case 1")
    {
        CacheType cache{2};

        // Cache is {{1, 1}}.
        cache.put(1UZ, 1);

        // Cache is {{1, 1}, {2, 2}}.
        cache.put(2UZ, 2);

        val = cache.get(1UZ);
        REQUIRE(val == 1);

        // LRU key was 2. Evicts key 2. Cache is {{1, 1}, {3, 3}}.
        cache.put(3UZ, 3);

        // Returns -1 (key not found).
        val = cache.get(2UZ);
        REQUIRE(val == -1);

        // LRU key was 1; evicts key 1, cache is {{4, 4}, {3, 3}}.
        cache.put(4UZ, 4);

        // Returns -1 (key not found).
        val = cache.get(1UZ);
        REQUIRE(val == -1);

        val = cache.get(3UZ);
        REQUIRE(val == 3);

        val = cache.get(4UZ);
        REQUIRE(val == 4);
    }

    SECTION("Test case 2")
    {
        CacheType cache(2);

        cache.put(1UZ, 1);

        val = cache.get(1UZ);
        REQUIRE(val == 1);

        cache.put(2UZ, 2);

        val = cache.get(2UZ);
        REQUIRE(val == 2);

        // Evicts key 1.
        cache.put(3UZ, 3);

        val = cache.get(1UZ);
        REQUIRE(val == -1);

        cache.put(2UZ, 4);

        val = cache.get(2UZ);
        REQUIRE(val == 4);

        // Evicts key 3.
        cache.put(4UZ, 4);

        val = cache.get(3UZ);
        REQUIRE(val == -1);

        val = cache.get(5UZ);
        REQUIRE(val == -1);
    }

    SECTION("Test case 3")
    {
        CacheType cache(1);

        cache.put(1UZ, 1);

        val = cache.get(1UZ);
        REQUIRE(val == 1);

        // Evicts key 1.
        cache.put(2UZ, 2);

        val = cache.get(1UZ);
        REQUIRE(val == -1);

        val = cache.get(2UZ);
        REQUIRE(val == 2);

        cache.put(2UZ, 3);

        val = cache.get(2UZ);
        REQUIRE(val == 3);
    }

    SECTION("Test case 4")
    {
        CacheType cache(3);

        cache.put(1UZ, 1);
        cache.put(2UZ, 2);
        cache.put(3UZ, 3);

        val = cache.get(1UZ);
        REQUIRE(val == 1);

        val = cache.get(2UZ);
        REQUIRE(val == 2);

        val = cache.get(3UZ);
        REQUIRE(val == 3);

        // Evicts key 1.
        cache.put(4UZ, 4);

        val = cache.get(1UZ);
        REQUIRE(val == -1);

        val = cache.get(4UZ);
        REQUIRE(val == 4);

        val = cache.get(2UZ);
        REQUIRE(val == 2);

        // Evicts key 3, as key 2 was accessed recently.
        cache.put(5UZ, 5);

        val = cache.get(3UZ);
        REQUIRE(val == -1);
    }
}
