// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <array>
#include <chrono>
#include <compare>
#include <cstddef>
#include <functional>
#include <ranges>
#include <thread>
#include <type_traits>
#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include "forfun/concurrency/spsc_bound_queue.hpp"

namespace {

struct dummy_aggregate {
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    int a;

    int b;

    int c;

    int d;
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    auto operator<=>(dummy_aggregate const&) const -> std::strong_ordering
        = default;
};

} // namespace

TEST_CASE("Wait-free SPSC append-only bounded queue", "[spsc_bound_queue]")
{
    SECTION("Initial span is empty")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 8> queue{};

        REQUIRE(queue.to_span().empty());
    }

    SECTION("Initially empty")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 8> const queue{};

        REQUIRE(queue.empty_unsafe());
    }

    SECTION("Capacity")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 16> const queue{};

        REQUIRE(queue.capacity() == 16UZ);
    }

    SECTION("Queue of std::byte")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<std::byte, 16> const
            queue{};

        REQUIRE(queue.capacity() == 16UZ);
    }

    SECTION("Emplace affects empty state")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 2> queue{};

        queue.emplace_back(677);

        REQUIRE_FALSE(queue.empty_unsafe());

        queue.emplace_back(683);

        REQUIRE_FALSE(queue.empty_unsafe());
    }

    SECTION("Emplace affects span size")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 4> queue{};

        queue.emplace_back(691);

        REQUIRE(queue.to_span().size() == 1UZ);

        queue.emplace_back(701);

        REQUIRE(queue.to_span().size() == 2UZ);

        queue.emplace_back(709);

        REQUIRE(queue.to_span().size() == 3UZ);

        queue.emplace_back(719);

        REQUIRE(queue.to_span().size() == 4UZ);
    }

    SECTION("Emplace affects span back")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 4> queue{};

        queue.emplace_back(-2);

        REQUIRE(queue.to_span().front() == -2);

        REQUIRE(queue.to_span().back() == -2);

        queue.emplace_back(0);

        REQUIRE(queue.to_span().back() == 0);

        queue.emplace_back(-3);

        REQUIRE(queue.to_span().back() == -3);

        queue.emplace_back(12);

        REQUIRE(queue.to_span().back() == 12);

        REQUIRE(queue.to_span().front() == -2);
    }

    SECTION("Emplace returns reference to emplaced element")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 4> queue{};

        decltype(auto) ref_to_emplaced{queue.emplace_back(225149)};

        static_assert(std::is_reference_v<decltype(ref_to_emplaced)>);

        REQUIRE(ref_to_emplaced == 225149);

        REQUIRE(queue.to_span().front() == 225149);

        ref_to_emplaced = 75773;

        REQUIRE(queue.to_span().front() == 75773);
    }

    SECTION("Emplace till full then read all")
    {
        using ValueType = int;

        static constexpr std::size_t const queue_capacity{8};

        forfun::concurrency::wait_free::
            spsc_bound_queue<ValueType, queue_capacity>
                queue{};

        for (
            ValueType const n :
            std::views::iota(ValueType{1}) | std::views::take(queue_capacity)
        )
        {
            auto const& ref{queue.emplace_back(n)};
            REQUIRE(ref == n);
        }

        REQUIRE_FALSE(queue.empty_unsafe());

        REQUIRE(queue.to_span().size() == queue_capacity);

        REQUIRE(
            std::ranges::equal(
                queue.to_span(),
                std::views::iota(ValueType{1})
                    | std::views::take(queue.to_span().size())
            )
        );
    }

    SECTION("To span")
    {
        forfun::concurrency::wait_free::spsc_bound_queue<int, 8> queue{};

        queue.emplace_back(727);
        queue.emplace_back(733);

        auto const consumable_span{queue.to_span()};

        REQUIRE(consumable_span.size() == 2UZ);

        REQUIRE(consumable_span.front() == 727);

        REQUIRE(consumable_span.back() == 733);
    }

    SECTION("Destructor call on empty queue")
    {
        {
            forfun::concurrency::wait_free::spsc_bound_queue<int, 8> const
                queue{};
        }

        SUCCEED();
    }

    SECTION("Destructor call on non-empty non-full queue")
    {
        {
            forfun::concurrency::wait_free::spsc_bound_queue<int, 8> queue{};
            queue.emplace_back(1);
            queue.emplace_back(2);
            queue.emplace_back(3);
        }

        SUCCEED();
    }

    SECTION("Destructor call on full queue")
    {
        {
            forfun::concurrency::wait_free::spsc_bound_queue<int, 8> queue{};
            queue.emplace_back(1);
            queue.emplace_back(2);
            queue.emplace_back(3);
            queue.emplace_back(4);
            queue.emplace_back(5);
            queue.emplace_back(6);
            queue.emplace_back(7);
            queue.emplace_back(8);
        }

        SUCCEED();
    }

    SECTION("Nondeterministic one producer and one consumer of int values")
    {
        using std::equal_to;

        static constexpr std::size_t const queue_size{8};

        static constexpr auto const expected
            = {208739, 208759, 208787, 208799, 208807, 208837, 208843, 208877};

        using SizeType = forfun::concurrency::wait_free::
            spsc_bound_queue<int, queue_size>::size_type;
        using ValueType = forfun::concurrency::wait_free::
            spsc_bound_queue<int, queue_size>::value_type;

        forfun::concurrency::wait_free::spsc_bound_queue<int, queue_size>
            queue{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(queue_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&queue, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < queue_size)
                {
                    for (auto&& val : queue.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        REQUIRE(std::ranges::contains(expected, val));
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == queue_size);
            });

            std::jthread const producer(
                [&queue, &produced_count] noexcept -> void {
                    for (auto&& val : expected)
                    {
                        queue.emplace_back(val);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == queue_size);

        REQUIRE(consumed_count == queue_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(queue.to_span().size() == queue_size);

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION(
        "Nondeterministic one producer and one consumer of aggregate values"
    )
    {
        using std::equal_to;

        static constexpr std::size_t const queue_size{8};

        using ValueType = dummy_aggregate;

        using SizeType = forfun::concurrency::wait_free::
            spsc_bound_queue<ValueType, queue_size>::size_type;

        forfun::concurrency::wait_free::spsc_bound_queue<ValueType, queue_size>
            queue{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(queue_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&queue, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < queue_size)
                {
                    for (auto&& val : queue.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == queue_size);
            });

            std::jthread const producer(
                [&queue, &produced_count] noexcept -> void {
                    for (
                        auto&& n :
                        std::views::iota(1) | std::views::take(queue_size)
                    )
                    {
                        queue.emplace_back(n * 11, n * 2, n * 5, n * 10);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == queue_size);

        REQUIRE(consumed_count == queue_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(queue.to_span().size() == queue_size);

        int generator_state{1};
        std::array<ValueType, queue_size> expected{};
        for (auto& val : expected)
        {
            auto const n{generator_state++};
            val = {.a = n * 11, .b = n * 2, .c = n * 5, .d = n * 10};
        }

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Nondeterministic one producer and one consumer of int values")
    {
        using std::chrono::operator""ms;
        using std::equal_to;

        static constexpr std::size_t const queue_size{8};

        static constexpr auto const expected
            = {208739, 208759, 208787, 208799, 208807, 208837, 208843, 208877};

        using SizeType = forfun::concurrency::wait_free::
            spsc_bound_queue<int, queue_size>::size_type;
        using ValueType = forfun::concurrency::wait_free::
            spsc_bound_queue<int, queue_size>::value_type;

        forfun::concurrency::wait_free::spsc_bound_queue<int, queue_size>
            queue{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(queue_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&queue, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < queue_size)
                {
                    for (auto&& val : queue.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        REQUIRE(std::ranges::contains(expected, val));
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == queue_size);
            });

            std::jthread const producer(
                [&queue, &produced_count] noexcept -> void {
                    std::this_thread::sleep_for(10ms);

                    for (auto&& val : expected)
                    {
                        std::this_thread::sleep_for(3ms);

                        queue.emplace_back(val);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == queue_size);

        REQUIRE(consumed_count == queue_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(queue.to_span().size() == queue_size);

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION(
        "Nondeterministic one producer and one consumer of aggregate values"
    )
    {
        using std::chrono::operator""ms;
        using std::equal_to;

        static constexpr std::size_t const queue_size{8};

        using ValueType = dummy_aggregate;

        using SizeType = forfun::concurrency::wait_free::
            spsc_bound_queue<ValueType, queue_size>::size_type;

        forfun::concurrency::wait_free::spsc_bound_queue<ValueType, queue_size>
            queue{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(queue_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&queue, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < queue_size)
                {
                    for (auto&& val : queue.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == queue_size);
            });

            std::jthread const producer(
                [&queue, &produced_count] noexcept -> void {
                    std::this_thread::sleep_for(10ms);

                    for (
                        auto&& n :
                        std::views::iota(1) | std::views::take(queue_size)
                    )
                    {
                        std::this_thread::sleep_for(10ms);

                        queue.emplace_back(n * 111, n * 4, n * 8, n * 20);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == queue_size);

        REQUIRE(consumed_count == queue_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(queue.to_span().size() == queue_size);

        int generator_state{1};
        std::array<ValueType, queue_size> expected{};
        for (auto& val : expected)
        {
            auto const n{generator_state++};
            val = {.a = n * 111, .b = n * 4, .c = n * 8, .d = n * 20};
        }

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Benchmark case")
    {
        static constexpr std::size_t const capacity{16};

        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int volatile val /*[[indeterminate]]*/;
        forfun::concurrency::wait_free::spsc_bound_queue<int, capacity> queue{};

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        queue.emplace_back(502807);
        val = queue.to_span().back();

        REQUIRE(val == 502807);
    }
}
