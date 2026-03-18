// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <list>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "forfun/sub_array_sums.hpp"

namespace {

template <typename Nums, typename Sums>
// clang-format off
concept template_specialization
    = requires(Nums nums, Sums sums, Nums::size_type sub_size) {
        forfun::sub_array_sums::sum_each(nums, sums, sub_size);
    };
// clang-format on

struct Dummy final {};

struct AddableDummy final {
    explicit(false) AddableDummy(auto const /*unused*/)
    {
    }

    [[maybe_unused]] auto operator+=(auto const /*unused*/) noexcept -> int
    {
        return 0;
    }

    [[maybe_unused]] auto operator-=(auto const /*unused*/) noexcept -> int
    {
        return 0;
    }

    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    [[maybe_unused]] explicit(false) operator int() const
    {
        return 0;
    }
};

template <typename SizeType>
struct DummyWithSizeType final : std::array<unsigned char, 0> {
    using size_type = SizeType;
};

} // namespace

TEST_CASE("Constraints of sub_array_sums", "[sub_array_sums]")
{
    SECTION("Positive")
    {
        STATIC_REQUIRE(
            template_specialization<std::array<int, 0>, std::array<int, 0>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<int>, std::vector<int>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<int>, std::array<int, 0>>
        );
        STATIC_REQUIRE(
            template_specialization<std::array<int, 0>, std::vector<int>>
        );
        STATIC_REQUIRE(
            template_specialization<std::array<int, 0>, std::list<int>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<int>, std::vector<unsigned>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<int>, std::vector<double>>
        );

        STATIC_REQUIRE(
            template_specialization<std::vector<unsigned>, std::vector<short>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<int>, std::vector<AddableDummy>>
        );
        STATIC_REQUIRE(
            template_specialization<
                DummyWithSizeType<std::vector<int>::size_type>,
                std::vector<int>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<AddableDummy>, std::vector<int>>
        );
    }

    SECTION("Negative")
    {
        STATIC_REQUIRE_FALSE(
            template_specialization<std::vector<int>, std::vector<std::string>>
        );
        STATIC_REQUIRE_FALSE(
            template_specialization<std::vector<std::string>, std::vector<int>>
        );
        STATIC_REQUIRE_FALSE(
            template_specialization<std::list<int>, std::array<int, 0>>
        );

        STATIC_REQUIRE_FALSE(
            template_specialization<std::vector<int>, std::vector<Dummy>>
        );
        STATIC_REQUIRE_FALSE(
            template_specialization<std::vector<int>, std::vector<Dummy>>
        );

        STATIC_REQUIRE_FALSE(template_specialization<int, int>);
        STATIC_REQUIRE_FALSE(template_specialization<int, std::vector<int>>);
        STATIC_REQUIRE_FALSE(template_specialization<std::vector<int>, int>);

        STATIC_REQUIRE_FALSE(
            template_specialization<DummyWithSizeType<char>, std::vector<int>>
        );
    }
}
