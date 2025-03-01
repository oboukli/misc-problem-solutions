// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <array>
#include <list>
#include <string>
#include <vector>

#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>

#include "forfun/sub_array_sums.hpp"

TEST_CASE("Sums of subarrays of length k", "[sub_array_sums]")
{
    using forfun::sub_array_sums::sum_each;

    SECTION(
        "Given an empty numbers collection"
        " when sums collection has one element,"
        " then sum is one element and is zero"
    )
    {
        std::vector<int> const numbers{};
        std::vector<int> sums(1);
        std::vector const expected{0};
        static constexpr auto const sub_size{0};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION(
        "Given an empty numbers collection"
        " when sums collection is empty,"
        " then no sum"
    )
    {
        std::vector<int> const numbers{};
        std::vector<int> sums{};
        std::vector<int> const expected{};
        static constexpr auto const sub_size{0};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("None of one")
    {
        std::vector const numbers{5};
        std::vector<int> sums(1);
        std::vector const expected{0};
        static constexpr auto const sub_size{0};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("None of two")
    {
        std::vector const numbers{{7, 11}};
        std::vector<int> sums(1);
        std::vector const expected{0};
        static constexpr auto const sub_size{0};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("One of one")
    {
        std::vector const numbers{13};
        std::vector<int> sums(1);
        std::vector const expected{13};
        static constexpr auto const sub_size{1};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("All of two")
    {
        std::vector const numbers{{2, 3}};
        std::vector<int> sums(1);
        std::vector const expected{5};
        static constexpr auto const sub_size{2};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("All of three")
    {
        std::vector const numbers{{3, 11, 17}};
        std::vector<int> sums(1);
        std::vector const expected{31};
        static constexpr auto const sub_size{3};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("One of two")
    {
        std::vector const numbers{{19, 23}};
        std::vector<int> sums(2);
        std::vector const expected{{19, 23}};
        static constexpr auto const sub_size{1};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("One of three")
    {
        std::vector const numbers{{29, 31, 37}};
        std::vector<int> sums(3);
        std::vector const expected{{29, 31, 37}};
        static constexpr auto const sub_size{1};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION(
        "Given non-empty array, "
        "when sub size is larger than size, "
        "then sum all"
    )
    {
        std::vector const numbers{{1, 2, 3}};
        std::vector<int> sums(1);
        std::vector const expected{6};
        static constexpr auto const sub_size{101};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("2 of 6")
    {
        std::vector const numbers{{1, 2, 2, 1, 1, 2}};
        std::vector<int> sums(5);
        std::vector const expected{{3, 4, 3, 2, 3}};
        static constexpr auto const sub_size{2};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6")
    {
        std::vector const numbers{{1, 1, 1, 2, 2, 2}};
        std::vector<int> sums(4);
        std::vector const expected{{3, 4, 5, 6}};
        static constexpr auto const sub_size{3};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take 2")
    {
        std::vector const numbers{{1, 1, 1, 2, 2, 2}};
        std::vector<int> sums(2);
        std::vector const expected{{3, 4}};
        static constexpr auto const sub_size{3};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take 3")
    {
        std::vector const numbers{{1, 1, 1, 2, 2, 2}};
        std::vector<int> sums(3);
        std::vector const expected{{3, 4, 5}};
        static constexpr auto const sub_size{3};

        CAPTURE(numbers);
        CAPTURE(sub_size);
        CAPTURE(sums.size());
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take all (std::array)")
    {
        static constexpr std::array const numbers{1, 1, 1, 2, 2, 2};
        std::array sums{3, 4, 5, 6};
        static constexpr std::array const expected{3, 4, 5, 6};
        static constexpr auto const sub_size{3};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("3 of 6, take all, do not mutate excess (std::array)")
    {
        static constexpr std::array const numbers{1, 1, 1, 2, 2, 2};
        std::array sums{-1, -1, -1, -1, -1, -1};
        static constexpr std::array const expected{3, 4, 5, 6, -1, -1};
        static constexpr auto const sub_size{3};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("Mixed iterators")
    {
        static constexpr std::array const numbers{1, 1, 1, 2, 2, 2};
        std::list sums{-1, -1, -1, -1, -1, -1};
        std::list const expected{3, 4, 5, 6, -1, -1};
        static constexpr auto const sub_size{3};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }

    SECTION("8 of 64 (benchmark case)")
    {
        constexpr std::array const numbers{
            // clang-format off
            1, 1, 1, 1, 1, 1, 1, 1,
            2, 2, 2, 2, 2, 2, 2, 2,
            3, 3, 3, 3, 3, 3, 3, 3,
            4, 4, 4, 4, 4, 4, 4, 4,
            5, 5, 5, 5, 5, 5, 5, 5,
            6, 6, 6, 6, 6, 6, 6, 6,
            7, 7, 7, 7, 7, 7, 7, 7,
            8, 8, 8, 8, 8, 8, 8, 8,
            // clang-format on
        };
        std::vector<int> sums(8);
        std::vector const expected{{8, 9, 10, 11, 12, 13, 14, 15}};
        static constexpr auto const sub_size{8};

        CAPTURE(numbers);
        CAPTURE(sums.size());
        CAPTURE(sub_size);
        sum_each(numbers, sums, sub_size);

        REQUIRE(sums == expected);
    }
}

namespace {

template <typename Nums, typename Sums>
// clang-format off
concept template_specialization
    = requires(Nums nums, Sums sums, typename Nums::size_type sub_size) {
        forfun::sub_array_sums::sum_each(nums, sums, sub_size);
    };
// clang-format on

struct Dummy final {};

struct AddableDummy final {
    explicit(false) AddableDummy(auto const /*unused*/)
    {
    }

    auto operator+=(auto const /*unused*/) noexcept -> int
    {
        return 0;
    }

    auto operator-=(auto const /*unused*/) noexcept -> int
    {
        return 0;
    }

    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    explicit(false) operator int() const
    {
        return 0;
    }
};

template <typename SizeType>
struct DummyWithSizeType final : public std::array<unsigned char, 0U> {
    using size_type = SizeType;
};

} // namespace

TEST_CASE("Constraints of sub_array_sums", "[sub_array_sums]")
{
    SECTION("Positive")
    {
        STATIC_REQUIRE(
            template_specialization<std::array<int, 0U>, std::array<int, 0U>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<int>, std::vector<int>>
        );
        STATIC_REQUIRE(
            template_specialization<std::vector<int>, std::array<int, 0U>>
        );
        STATIC_REQUIRE(
            template_specialization<std::array<int, 0U>, std::vector<int>>
        );
        STATIC_REQUIRE(
            template_specialization<std::array<int, 0U>, std::list<int>>
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
            template_specialization<std::list<int>, std::array<int, 0U>>
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
