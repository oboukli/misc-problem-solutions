// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/lru_cache.hpp"

TEMPLATE_TEST_CASE(
    "LRU Cache",
    "[lru_cache]",
    (forfun::lrucache::naive::LRUCache),
    (forfun::lrucache::stl::LRUCache))
{
    using CacheType = TestType;

    STATIC_REQUIRE(forfun::lrucache::concepts::lru_cache<CacheType>);

    int volatile val{};

    SECTION("Test case 1")
    {
        CacheType cache{2};

        // Cache is {{1, 1}}.
        cache.put(1, 1);

        // Cache is {{1, 1}, {2, 2}}.
        cache.put(2, 2);

        val = cache.get(1);
        REQUIRE(val == 1);

        // LRU key was 2. Evicts key 2. Cache is {{1, 1}, {3, 3}}.
        cache.put(3, 3);

        // Returns -1 (key not found).
        val = cache.get(2);
        REQUIRE(val == -1);

        // LRU key was 1; evicts key 1, cache is {{4, 4}, {3, 3}}.
        cache.put(4, 4);

        // Returns -1 (key not found).
        val = cache.get(1);
        REQUIRE(val == -1);

        val = cache.get(3);
        REQUIRE(val == 3);

        val = cache.get(4);
        REQUIRE(val == 4);
    }

    SECTION("Test case 2")
    {
        CacheType cache(2);

        cache.put(1, 1);

        val = cache.get(1);
        REQUIRE(val == 1);

        cache.put(2, 2);

        val = cache.get(2);
        REQUIRE(val == 2);

        // Evicts key 1.
        cache.put(3, 3);

        val = cache.get(1);
        REQUIRE(val == -1);

        cache.put(2, 4);

        val = cache.get(2);
        REQUIRE(val == 4);

        // Evicts key 3.
        cache.put(4, 4);

        val = cache.get(3);
        REQUIRE(val == -1);

        val = cache.get(5);
        REQUIRE(val == -1);
    }

    SECTION("Test case 3")
    {
        CacheType cache(1);

        cache.put(1, 1);

        val = cache.get(1);
        REQUIRE(val == 1);

        // Evicts key 1.
        cache.put(2, 2);

        val = cache.get(1);
        REQUIRE(val == -1);

        val = cache.get(2);
        REQUIRE(val == 2);

        cache.put(2, 3);

        val = cache.get(2);
        REQUIRE(val == 3);
    }

    SECTION("Test case 4")
    {
        CacheType cache(3);

        cache.put(1, 1);
        cache.put(2, 2);
        cache.put(3, 3);

        val = cache.get(1);
        REQUIRE(val == 1);

        val = cache.get(2);
        REQUIRE(val == 2);

        val = cache.get(3);
        REQUIRE(val == 3);

        // Evicts key 1.
        cache.put(4, 4);

        val = cache.get(1);
        REQUIRE(val == -1);

        val = cache.get(4);
        REQUIRE(val == 4);

        val = cache.get(2);
        REQUIRE(val == 2);

        // Evicts key 3, as key 2 was accessed recently.
        cache.put(5, 5);

        val = cache.get(3);
        REQUIRE(val == -1);
    }
}

TEST_CASE("LRU Cache concepts", "[lru_cache]")
{
    struct Dummy0 {};

    struct Dummy1 : public Dummy0 {
        Dummy1(std::size_t)
        {
        }
    };

    struct Dummy2 : public Dummy1 {
        Dummy2(std::size_t c) : Dummy1{c}
        {
        }

        void put(std::size_t, int)
        {
        }
    };

    struct Dummy3 : public Dummy2 {
        Dummy3(std::size_t c) : Dummy2{c}
        {
        }

        int get(std::size_t)
        {
            return 0;
        }
    };

    struct Dummy4 : public Dummy3 {
        Dummy4(std::size_t c) : Dummy3{c}
        {
        }

        void dummy()
        {
        }
    };

    SECTION("Positive")
    {
        STATIC_REQUIRE(forfun::lrucache::concepts::lru_cache<Dummy3>);
        STATIC_REQUIRE(forfun::lrucache::concepts::lru_cache<Dummy4>);
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(forfun::lrucache::concepts::lru_cache<int>);
        STATIC_REQUIRE_FALSE(forfun::lrucache::concepts::lru_cache<Dummy0>);
        STATIC_REQUIRE_FALSE(forfun::lrucache::concepts::lru_cache<Dummy1>);
        STATIC_REQUIRE_FALSE(forfun::lrucache::concepts::lru_cache<Dummy2>);
    }
}
