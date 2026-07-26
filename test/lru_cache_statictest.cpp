// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/lru_cache.hpp"

TEST_CASE("LRU cache concepts", "[lru_cache]")
{
    struct Dummy0 {};

    struct Dummy1 : Dummy0 {
        explicit Dummy1(std::size_t /*unused*/) noexcept
        {
        }
    };

    struct Dummy2 : Dummy1 {
        explicit Dummy2(std::size_t const capacity) noexcept : Dummy1{capacity}
        {
        }

        [[maybe_unused]] auto
        put(std::size_t /*unused*/, int /*unused*/) noexcept -> void
        {
        }
    };

    class Dummy3 : public Dummy2 {
    public:
        explicit Dummy3(std::size_t const capacity) noexcept : Dummy2{capacity}
        {
        }

        [[maybe_unused]] [[nodiscard]] auto
        get(std::size_t /*unused*/) const noexcept -> int
        {
            return value_;
        }

    private:
        int value_{};
    };

    struct Dummy4 final : Dummy3 {
        [[maybe_unused]] explicit Dummy4(std::size_t const capacity) noexcept :
            Dummy3{capacity}
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

TEMPLATE_TEST_CASE(
    "LRU cache",
    "[lru_cache]",
    forfun::lrucache::naive::LRUCache,
    forfun::lrucache::stl::LRUCache
)
{
    using CacheType = TestType;

    STATIC_REQUIRE(forfun::lrucache::concepts::lru_cache<CacheType>);
}
