// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <atomic>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <exception>
#include <limits>
#include <new>
#include <span>
#include <type_traits>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include <forfun/concurrency/swmr_append_buffer.hpp>

namespace {

template <typename Type, std::size_t Size, std::size_t Separation>
concept instantiable_swmr_append_buffer = requires {
    typename forfun::concurrency::wait_free::
        swmr_append_buffer<Type, Size, Separation>;
};

// NOLINTNEXTLINE(cppcoreguidelines-special-member-functions)
struct dummy_with_throwing_destructor final {
    // NOLINTNEXTLINE(bugprone-unsafe-to-allow-exceptions)
    [[noreturn]] ~dummy_with_throwing_destructor() noexcept(false)
    {
        throw std::exception();
    }
};

#ifdef _MSC_VER
#pragma warning(push)
// Warning C4324: 'type': structure was padded due to alignment specifier.
#pragma warning(disable : 4324)
#endif // _MSC_VER

struct alignas(128) over_aligned_dummy_type_for_static_test {
    int dummy_;
};

#ifdef _MSC_VER
#pragma warning(pop) // C4324
#endif // _MSC_VER

} // namespace

TEST_CASE("Wait-free SWMR append buffer", "[swmr_append_buffer]")
{
    SECTION("Object representations is not unique")
    {
        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::swmr_append_buffer<
                    char,
                    8UZ,
                    std::hardware_destructive_interference_size>>
        );

        STATIC_REQUIRE_FALSE(
            std::has_unique_object_representations_v<
                forfun::concurrency::wait_free::swmr_append_buffer<
                    int,
                    8UZ,
                    std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Construction and initialization")
    {
        STATIC_REQUIRE_FALSE(
            std::copyable<forfun::concurrency::wait_free::swmr_append_buffer<
                int,
                8UZ,
                std::hardware_destructive_interference_size>>
        );

        STATIC_REQUIRE_FALSE(
            std::movable<forfun::concurrency::wait_free::swmr_append_buffer<
                int,
                8UZ,
                std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Comparison")
    {
        STATIC_REQUIRE_FALSE(
            std::equality_comparable<
                forfun::concurrency::wait_free::swmr_append_buffer<
                    int,
                    8UZ,
                    std::hardware_destructive_interference_size>>
        );
    }

    SECTION("Capacity is as requested")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(buffer_type::capacity() == 8UZ);
    }

    SECTION("Capacity can be odd")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            3UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(buffer_type::capacity() == 3UZ);
    }

    SECTION("Type aliases")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(std::same_as<buffer_type::size_type, std::size_t>);

        STATIC_REQUIRE(std::same_as<buffer_type::value_type, int>);

        STATIC_REQUIRE(std::same_as<buffer_type::const_reference, int const&>);
    }

    SECTION("To span")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(std::same_as<buffer_type::span_type, std::span<int>>);

        STATIC_REQUIRE(
            std::same_as<
                buffer_type::span_type,
                decltype(std::declval<buffer_type>().to_span())>
        );
    }

    SECTION("Return type of emplace_back is const reference")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(
            std::same_as<
                buffer_type::const_reference,
                decltype(std::declval<buffer_type>().emplace_back(int{}))>
        );
    }

    SECTION("Return type of reset_unsafe is void")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(
            std::same_as<
                void,
                decltype(std::declval<buffer_type>().reset_unsafe())>
        );
    }

    SECTION("Alignment")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(
            alignof(buffer_type) == std::hardware_destructive_interference_size
        );
    }

    SECTION("Custom cache-line separation")
    {
        using buffer_type = forfun::concurrency::wait_free::
            swmr_append_buffer<int, 8UZ, 32UZ>;

        STATIC_REQUIRE(alignof(buffer_type) == 32UZ);
    }

    SECTION("Over-aligned element type")
    {
        using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
            over_aligned_dummy_type_for_static_test,
            8UZ,
            std::hardware_destructive_interference_size>;

        STATIC_REQUIRE(
            alignof(buffer_type)
            >= alignof(over_aligned_dummy_type_for_static_test)
        );
    }
}

TEST_CASE("Wait-free SWMR append buffer constraints", "[swmr_append_buffer]")
{
    constexpr auto max_object_size{
        static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max())
    };

    SECTION("Positive")
    {
        STATIC_REQUIRE(
            instantiable_swmr_append_buffer<char, max_object_size, 64UZ>
        );

        STATIC_REQUIRE(instantiable_swmr_append_buffer<int, 4UZ, 64UZ>);

        STATIC_REQUIRE(instantiable_swmr_append_buffer<int, 4UZ, 128UZ>);

        STATIC_REQUIRE(
            instantiable_swmr_append_buffer<
                std::size_t,
                1UZ,
                alignof(std::atomic<std::size_t>)>
        );

        STATIC_REQUIRE(
            instantiable_swmr_append_buffer<
                over_aligned_dummy_type_for_static_test,
                3UZ,
                64UZ>
        );
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(instantiable_swmr_append_buffer<void, 4UZ, 64UZ>);

        STATIC_REQUIRE_FALSE(instantiable_swmr_append_buffer<int&, 4UZ, 64UZ>);

        STATIC_REQUIRE_FALSE(instantiable_swmr_append_buffer<int(), 4UZ, 64UZ>);

        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<int const, 4UZ, 64UZ>
        );

        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<int volatile, 4UZ, 64UZ>
        );

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<int[3], 4UZ, 64UZ>
        );

        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<
                dummy_with_throwing_destructor,
                4UZ,
                64UZ>
        );

        STATIC_REQUIRE_FALSE(instantiable_swmr_append_buffer<int, 0UZ, 64UZ>);

        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<char, max_object_size + 1UZ, 64UZ>
        );

        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<
                std::uint32_t,
                max_object_size + 1UZ,
                64UZ>
        );

        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<
                std::uint32_t,
                // clang-format off
                (std::numeric_limits<std::size_t>::max()
                    / sizeof(std::uint32_t)) + 1UZ,
                // clang-format on
                64UZ>
        );

        STATIC_REQUIRE_FALSE(instantiable_swmr_append_buffer<int, 4UZ, 48UZ>);

        STATIC_REQUIRE_FALSE(
            instantiable_swmr_append_buffer<
                int,
                4UZ,
                alignof(std::atomic<std::size_t>) / 2UZ>
        );
    }
}
