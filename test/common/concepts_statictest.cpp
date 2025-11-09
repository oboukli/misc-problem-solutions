// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cstddef>
#include <cstdint>
#include <string>

#include <catch2/catch_test_macros.hpp>

#include "forfun/common/concepts.hpp"

namespace {

struct AddableDummy final {
    [[maybe_unused]] auto
    operator+(AddableDummy const& /*unused*/) const noexcept -> AddableDummy
    {
        return *this;
    }
};

struct Dummy final {};

struct MultipliableDummy final {
    [[maybe_unused]] auto
    operator*(MultipliableDummy const& /*unused*/) const noexcept
        -> MultipliableDummy
    {
        return *this;
    }
};

} // namespace

TEST_CASE("Concept addition_unpromoted", "[common]")
{
    using forfun::common::concepts::addition_unpromoted;

    SECTION("Positive")
    {
        STATIC_REQUIRE(addition_unpromoted<int>);
        STATIC_REQUIRE(addition_unpromoted<unsigned int>);

        STATIC_REQUIRE(addition_unpromoted<std::int32_t>);
        STATIC_REQUIRE(addition_unpromoted<std::uint32_t>);
        STATIC_REQUIRE(addition_unpromoted<std::size_t>);
        STATIC_REQUIRE(addition_unpromoted<std::int64_t>);
        STATIC_REQUIRE(addition_unpromoted<std::uint64_t>);

        STATIC_REQUIRE(addition_unpromoted<float>);
        STATIC_REQUIRE(addition_unpromoted<double>);

        STATIC_REQUIRE(addition_unpromoted<std::string>);

        STATIC_REQUIRE(addition_unpromoted<AddableDummy>);
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(addition_unpromoted<char>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<short>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<unsigned short>);

        STATIC_REQUIRE_FALSE(addition_unpromoted<std::int8_t>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<std::uint8_t>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<std::int16_t>);
        STATIC_REQUIRE_FALSE(addition_unpromoted<std::uint16_t>);

        STATIC_REQUIRE_FALSE(addition_unpromoted<Dummy>);
    }
}

TEST_CASE("Concept multipliable_as", "[common]")
{
    using forfun::common::concepts::multipliable_as;

    SECTION("Positive")
    {
        STATIC_REQUIRE(multipliable_as<int, int>);
        STATIC_REQUIRE(multipliable_as<char, int>);
        STATIC_REQUIRE(multipliable_as<short, int>);
        STATIC_REQUIRE(multipliable_as<unsigned int, unsigned int>);

        STATIC_REQUIRE(multipliable_as<std::int32_t, std::int32_t>);
        STATIC_REQUIRE(multipliable_as<std::uint32_t, std::uint32_t>);
        STATIC_REQUIRE(multipliable_as<std::size_t, std::size_t>);
        STATIC_REQUIRE(multipliable_as<std::int64_t, std::int64_t>);
        STATIC_REQUIRE(multipliable_as<std::uint64_t, std::uint64_t>);

        STATIC_REQUIRE(multipliable_as<MultipliableDummy, MultipliableDummy>);
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(multipliable_as<int, char>);

        STATIC_REQUIRE_FALSE(multipliable_as<std::int32_t, short>);
        STATIC_REQUIRE_FALSE(multipliable_as<std::uint32_t, unsigned short>);
        STATIC_REQUIRE_FALSE(multipliable_as<int, std::int8_t>);
        STATIC_REQUIRE_FALSE(multipliable_as<int, std::uint8_t>);
        STATIC_REQUIRE_FALSE(multipliable_as<std::int32_t, std::int16_t>);
        STATIC_REQUIRE_FALSE(multipliable_as<std::int32_t, std::uint16_t>);
        STATIC_REQUIRE_FALSE(multipliable_as<std::int32_t, std::uint32_t>);

        STATIC_REQUIRE_FALSE(multipliable_as<int, float>);
        STATIC_REQUIRE_FALSE(multipliable_as<int, double>);

        STATIC_REQUIRE_FALSE(multipliable_as<int, std::string>);
        STATIC_REQUIRE_FALSE(multipliable_as<std::string, int>);

        STATIC_REQUIRE_FALSE(multipliable_as<int, Dummy>);
        STATIC_REQUIRE_FALSE(multipliable_as<Dummy, int>);
        STATIC_REQUIRE_FALSE(multipliable_as<Dummy, Dummy>);
    }
}

TEST_CASE("Concept noexcept_callable", "[common]")
{
    using forfun::common::concepts::noexcept_callable;

    SECTION("Positive")
    {
        STATIC_REQUIRE(noexcept_callable<auto() noexcept -> void>);
        STATIC_REQUIRE(noexcept_callable<auto(int) noexcept -> void, int>);
        STATIC_REQUIRE(
            noexcept_callable<auto(int, int) noexcept -> void, int, int>
        );
        STATIC_REQUIRE(
            noexcept_callable<auto(int, char*) noexcept -> void, double, char*>
        );
        STATIC_REQUIRE(
            noexcept_callable<
                auto(int, std::string_view) noexcept -> void,
                int,
                std::string>
        );
    }

    SECTION("Negative")
    {
        SECTION("noexcept is false")
        {
            STATIC_REQUIRE_FALSE(noexcept_callable<auto()->void>);
        }

        SECTION("Parameter type mismatch")
        {
            STATIC_REQUIRE_FALSE(
                noexcept_callable<
                    auto(int, std::vector<char>&) noexcept -> void,
                    std::string,
                    std::vector<char>&>
            );
            STATIC_REQUIRE_FALSE(
                noexcept_callable<auto(int, int&) noexcept -> void, int, int>
            );
            STATIC_REQUIRE_FALSE(
                noexcept_callable<auto(char, char&) noexcept -> void, int, int&>
            );
        }

        SECTION("Parameter list mismatch")
        {
            STATIC_REQUIRE_FALSE(
                noexcept_callable<auto() noexcept -> void, int, int>
            );
            STATIC_REQUIRE_FALSE(noexcept_callable<auto(int) noexcept -> void>);

            STATIC_REQUIRE_FALSE(
                noexcept_callable<auto(int) noexcept -> void, int, int>
            );
            STATIC_REQUIRE_FALSE(
                noexcept_callable<auto(int, int) noexcept -> void>
            );
        }
    }
}
