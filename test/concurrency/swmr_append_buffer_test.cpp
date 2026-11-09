// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <new>
#include <ranges>
#include <thread>
#include <type_traits>
#include <vector>

#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <catch2/matchers/catch_matchers_range_equals.hpp>

#include <forfun/concurrency/swmr_append_buffer.hpp>

namespace {

struct dummy_aggregate final {
    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    int a;

    int b;

    int c;

    int d;
    // NOLINTEND(misc-non-private-member-variables-in-classes)

    auto operator==(dummy_aggregate const&) const -> bool = default;
};

struct dummy_with_tracked_destructor final {
private:
    static inline std::atomic<std::size_t> alive_instances_{};

    static inline std::atomic<std::size_t> destructor_calls_{};

    int dummy_value_;

public:
    static auto reset_destructor_call_counter() noexcept -> void
    {
        std::atomic_store_explicit(
            &destructor_calls_, 0UZ, std::memory_order_relaxed
        );
    }

    [[nodiscard]] static auto alive_instances() noexcept -> std::size_t
    {
        return std::atomic_load_explicit(
            &alive_instances_, std::memory_order_relaxed
        );
    }

    [[nodiscard]] static auto destructor_calls() noexcept -> std::size_t
    {
        return std::atomic_load_explicit(
            &destructor_calls_, std::memory_order_relaxed
        );
    }

    explicit dummy_with_tracked_destructor(int dummy_value) noexcept :
        dummy_value_{dummy_value}
    {
        std::atomic_fetch_add_explicit(
            &alive_instances_, 1UZ, std::memory_order_relaxed
        );
    }

    dummy_with_tracked_destructor(dummy_with_tracked_destructor const&) noexcept
        = default;

    dummy_with_tracked_destructor(dummy_with_tracked_destructor&&) noexcept
        = default;

    ~dummy_with_tracked_destructor()
    {
        std::atomic_fetch_sub_explicit(
            &alive_instances_, 1UZ, std::memory_order_relaxed
        );

        std::atomic_fetch_add_explicit(
            &destructor_calls_, 1UZ, std::memory_order_relaxed
        );
    }

    auto operator=(dummy_with_tracked_destructor const&) noexcept
        -> dummy_with_tracked_destructor& = default;

    auto operator=(dummy_with_tracked_destructor&&) noexcept
        -> dummy_with_tracked_destructor& = default;

    [[nodiscard]] auto get_value() const noexcept -> int
    {
        return dummy_value_;
    }
};

static_assert(
    std::is_nothrow_constructible_v<dummy_with_tracked_destructor, int>
);

class destructor_call_counter_guard final {
public:
    destructor_call_counter_guard() noexcept
    {
        dummy_with_tracked_destructor::reset_destructor_call_counter();
    }

    destructor_call_counter_guard(destructor_call_counter_guard const&)
        = delete;

    destructor_call_counter_guard(destructor_call_counter_guard&&) = delete;

    ~destructor_call_counter_guard()
    {
        dummy_with_tracked_destructor::reset_destructor_call_counter();
    }

    auto operator=(destructor_call_counter_guard const&)
        -> destructor_call_counter_guard& = delete;

    auto operator=(destructor_call_counter_guard&&)
        -> destructor_call_counter_guard& = delete;
};

} // namespace

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdisabled-macro-expansion"
#endif // __clang__

TEMPLATE_TEST_CASE_SIG(
    "Wait-free SWMR append buffer",
    "[swmr_append_buffer]",
    ((typename Type, std::size_t Size), Type, Size),
    (int, 4UZ),
    (int, 8UZ),
    (int, 16UZ)
)
{
    using buffer_type = forfun::concurrency::wait_free::swmr_append_buffer<
        Type,
        Size,
        std::hardware_destructive_interference_size>;

    SECTION("Initial span is empty")
    {
        buffer_type buffer{};

        REQUIRE(buffer.to_span().empty());
    }

    SECTION("Initially empty")
    {
        buffer_type const buffer{};

        REQUIRE(buffer.empty());
    }

    SECTION("Capacity is as requested")
    {
        buffer_type const buffer{};

        REQUIRE(buffer.capacity() == Size);
    }

    SECTION("Emplace affects empty state")
    {
        buffer_type buffer{};

        buffer.emplace_back(677);

        REQUIRE_FALSE(buffer.empty());

        buffer.emplace_back(683);

        REQUIRE_FALSE(buffer.empty());
    }

    SECTION("Emplace affects span size")
    {
        buffer_type buffer{};

        buffer.emplace_back(691);

        REQUIRE(buffer.to_span().size() == 1UZ);

        buffer.emplace_back(701);

        REQUIRE(buffer.to_span().size() == 2UZ);

        buffer.emplace_back(709);

        REQUIRE(buffer.to_span().size() == 3UZ);

        buffer.emplace_back(719);

        REQUIRE(buffer.to_span().size() == 4UZ);
    }

    SECTION("Emplace affects span back")
    {
        buffer_type buffer{};

        buffer.emplace_back(-2);

        REQUIRE(buffer.to_span().front() == -2);

        REQUIRE(buffer.to_span().back() == -2);

        buffer.emplace_back(0);

        REQUIRE(buffer.to_span().back() == 0);

        buffer.emplace_back(-3);

        REQUIRE(buffer.to_span().back() == -3);

        buffer.emplace_back(12);

        REQUIRE(buffer.to_span().back() == 12);

        REQUIRE(buffer.to_span().front() == -2);
    }

    SECTION("Emplace returns reference to emplaced element")
    {
        buffer_type buffer{};

        decltype(auto) ref_to_emplaced{buffer.emplace_back(225149)};

        static_assert(std::is_reference_v<decltype(ref_to_emplaced)>);

        REQUIRE(ref_to_emplaced == 225149);

        REQUIRE(buffer.to_span().front() == 225149);

        ref_to_emplaced = 75773;

        REQUIRE(buffer.to_span().front() == 75773);
    }

    SECTION("Emplace till full then read all")
    {
        using ValueType = int;

        constexpr std::size_t const buffer_capacity{8};

        buffer_type buffer{};

        for (
            ValueType const n :
            std::views::iota(ValueType{1}) | std::views::take(buffer_capacity)
        )
        {
            auto const& ref{buffer.emplace_back(n)};
            REQUIRE(ref == n);
        }

        REQUIRE_FALSE(buffer.empty());

        REQUIRE(buffer.to_span().size() == buffer_capacity);

        REQUIRE(
            std::ranges::equal(
                buffer.to_span(),
                std::views::iota(ValueType{1})
                    | std::views::take(buffer.to_span().size())
            )
        );
    }

    SECTION("To span")
    {
        buffer_type buffer{};

        buffer.emplace_back(727);
        buffer.emplace_back(733);

        auto const consumable_span{buffer.to_span()};

        REQUIRE(consumable_span.size() == 2UZ);

        REQUIRE(consumable_span.front() == 727);

        REQUIRE(consumable_span.back() == 733);
    }

    SECTION("Reset call on empty buffer")
    {
        buffer_type buffer{};

        buffer.reset_unsafe();

        REQUIRE(buffer.empty());
    }

    SECTION("Reset call on non-empty non-full buffer")
    {
        buffer_type buffer{};
        buffer.emplace_back(1);
        buffer.emplace_back(2);
        buffer.emplace_back(3);

        buffer.reset_unsafe();

        REQUIRE(buffer.empty());
    }

    SECTION("Destructor call on empty buffer")
    {
        {
            buffer_type const buffer{};
        }

        SUCCEED();
    }

    SECTION("Destructor call on non-empty buffer")
    {
        {
            buffer_type buffer{};
            buffer.emplace_back(1);
        }

        SUCCEED();
    }

    SECTION("Destructor call on non-empty non-full buffer")
    {
        {
            buffer_type buffer{};
            buffer.emplace_back(1);
            buffer.emplace_back(2);
            buffer.emplace_back(3);
        }

        SUCCEED();
    }
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

TEST_CASE(
    "Wait-free SWMR append buffer (miscellaneous cases)", "[swmr_append_buffer]"
)
{
    SECTION("Initial span is empty")
    {
        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            1,
            std::hardware_destructive_interference_size>
            buffer{};

        REQUIRE(buffer.to_span().empty());
    }

    SECTION("Initially empty")
    {
        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            1,
            std::hardware_destructive_interference_size> const buffer{};

        REQUIRE(buffer.empty());
    }

    SECTION("Capacity is as requested")
    {
        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            1,
            std::hardware_destructive_interference_size> const buffer{};

        REQUIRE(buffer.capacity() == 1UZ);
    }

    SECTION("Single-slot buffer resets cleanly and refills")
    {
        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            1,
            std::hardware_destructive_interference_size>
            buffer{};

        buffer.emplace_back(11);

        REQUIRE(buffer.to_span().size() == 1UZ);

        REQUIRE(buffer.to_span().front() == 11);

        buffer.reset_unsafe();

        REQUIRE(buffer.empty());

        REQUIRE(buffer.to_span().empty());

        buffer.emplace_back(17);

        REQUIRE(buffer.to_span().size() == 1UZ);

        REQUIRE(buffer.to_span().front() == 17);

        REQUIRE(buffer.to_span().back() == 17);
    }

    SECTION("Reset call on full buffer")
    {
        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8,
            std::hardware_destructive_interference_size>
            buffer{};
        buffer.emplace_back(1);
        buffer.emplace_back(2);
        buffer.emplace_back(3);
        buffer.emplace_back(4);
        buffer.emplace_back(5);
        buffer.emplace_back(6);
        buffer.emplace_back(7);
        buffer.emplace_back(8);

        buffer.reset_unsafe();

        REQUIRE(buffer.empty());
    }

    SECTION("Fill, reset, refill, and read buffer")
    {
        using ValueType = int;

        constexpr std::size_t const buffer_capacity{8};

        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            8,
            std::hardware_destructive_interference_size>
            buffer{};
        buffer.emplace_back(10);
        buffer.emplace_back(20);
        buffer.emplace_back(30);
        buffer.emplace_back(40);
        buffer.emplace_back(50);
        buffer.emplace_back(60);
        buffer.emplace_back(70);
        buffer.emplace_back(80);

        buffer.reset_unsafe();

        REQUIRE(buffer.empty());

        buffer.emplace_back(1);
        buffer.emplace_back(2);
        buffer.emplace_back(3);
        buffer.emplace_back(4);
        buffer.emplace_back(5);
        buffer.emplace_back(6);
        buffer.emplace_back(7);
        buffer.emplace_back(8);

        REQUIRE_FALSE(buffer.empty());

        REQUIRE(buffer.to_span().size() == buffer_capacity);

        REQUIRE(
            std::ranges::equal(
                buffer.to_span(),
                std::views::iota(ValueType{1})
                    | std::views::take(buffer.to_span().size())
            )
        );
    }

    SECTION("Destructor call on full buffer")
    {
        {
            forfun::concurrency::wait_free::swmr_append_buffer<
                int,
                8,
                std::hardware_destructive_interference_size>
                buffer{};
            buffer.emplace_back(1);
            buffer.emplace_back(2);
            buffer.emplace_back(3);
            buffer.emplace_back(4);
            buffer.emplace_back(5);
            buffer.emplace_back(6);
            buffer.emplace_back(7);
            buffer.emplace_back(8);
        }

        SUCCEED();
    }

    SECTION("Reset destroys bufferd non-trivial objects")
    {
        destructor_call_counter_guard const guard;
        {
            forfun::concurrency::wait_free::swmr_append_buffer<
                dummy_with_tracked_destructor,
                4,
                std::hardware_destructive_interference_size>
                buffer{};

            buffer.emplace_back(584141);
            buffer.emplace_back(604171);
            buffer.emplace_back(971767);

            REQUIRE_FALSE(buffer.empty());

            REQUIRE(dummy_with_tracked_destructor::alive_instances() == 3UZ);

            REQUIRE(buffer.to_span().size() == 3UZ);

            REQUIRE(buffer.to_span().front().get_value() == 584141);

            REQUIRE(dummy_with_tracked_destructor::destructor_calls() == 0UZ);

            buffer.reset_unsafe();

            REQUIRE(buffer.empty());

            REQUIRE(dummy_with_tracked_destructor::alive_instances() == 0UZ);
        }

        REQUIRE(dummy_with_tracked_destructor::destructor_calls() == 3UZ);

        REQUIRE(dummy_with_tracked_destructor::alive_instances() == 0UZ);
    }

    SECTION("Destructor destroys buffered non-trivial objects")
    {
        destructor_call_counter_guard const guard;
        {
            forfun::concurrency::wait_free::swmr_append_buffer<
                dummy_with_tracked_destructor,
                4,
                std::hardware_destructive_interference_size>
                buffer{};

            buffer.emplace_back(1062599);
            buffer.emplace_back(1282529);

            REQUIRE_FALSE(buffer.empty());

            REQUIRE(dummy_with_tracked_destructor::alive_instances() == 2UZ);

            REQUIRE(buffer.to_span().size() == 2UZ);

            REQUIRE(buffer.to_span().front().get_value() == 1062599);

            REQUIRE(dummy_with_tracked_destructor::destructor_calls() == 0UZ);

            REQUIRE(dummy_with_tracked_destructor::alive_instances() == 2UZ);
        }

        REQUIRE(dummy_with_tracked_destructor::destructor_calls() == 2UZ);

        REQUIRE(dummy_with_tracked_destructor::alive_instances() == 0UZ);
    }

    SECTION(
        "Nondeterministic one producer and one consumer of int values "
        "(immediate write)"
    )
    {
        constexpr std::size_t const buffer_size{8};

        static constexpr auto const expected
            = {208739, 208759, 208787, 208799, 208807, 208837, 208843, 208877};

        using SizeType = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            buffer_size,
            std::hardware_destructive_interference_size>::size_type;
        using ValueType = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            buffer_size,
            std::hardware_destructive_interference_size>::value_type;

        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            buffer_size,
            std::hardware_destructive_interference_size>
            buffer{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(buffer_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&buffer, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < buffer_size)
                {
                    for (auto&& val : buffer.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        REQUIRE(std::ranges::contains(expected, val));
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == buffer_size);
            });

            std::jthread const producer(
                [&buffer, &produced_count] noexcept -> void {
                    for (auto&& val : expected)
                    {
                        buffer.emplace_back(val);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == buffer_size);

        REQUIRE(consumed_count == buffer_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(buffer.to_span().size() == buffer_size);

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION(
        "Nondeterministic one producer and one consumer of aggregate values "
        "(immediate write)"
    )
    {
        static constexpr std::size_t const buffer_size{8};

        using ValueType = dummy_aggregate;

        using SizeType = forfun::concurrency::wait_free::swmr_append_buffer<
            ValueType,
            buffer_size,
            std::hardware_destructive_interference_size>::size_type;

        forfun::concurrency::wait_free::swmr_append_buffer<
            ValueType,
            buffer_size,
            std::hardware_destructive_interference_size>
            buffer{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(buffer_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&buffer, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < buffer_size)
                {
                    for (auto&& val : buffer.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == buffer_size);
            });

            std::jthread const producer(
                [&buffer, &produced_count] noexcept -> void {
                    for (
                        auto&& n :
                        std::views::iota(1) | std::views::take(buffer_size)
                    )
                    {
                        buffer.emplace_back(n * 11, n * 2, n * 5, n * 10);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == buffer_size);

        REQUIRE(consumed_count == buffer_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(buffer.to_span().size() == buffer_size);

        int generator_state{1};
        std::array<ValueType, buffer_size> expected{};
        for (auto& val : expected)
        {
            auto const n{generator_state++};
            val = {.a = n * 11, .b = n * 2, .c = n * 5, .d = n * 10};
        }

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION(
        "Nondeterministic one producer and one consumer of int values (delayed "
        "producer)"
    )
    {
        using std::chrono::operator""ms;

        constexpr std::size_t const buffer_size{8};

        static constexpr auto const expected
            = {208739, 208759, 208787, 208799, 208807, 208837, 208843, 208877};

        using SizeType = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            buffer_size,
            std::hardware_destructive_interference_size>::size_type;
        using ValueType = forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            buffer_size,
            std::hardware_destructive_interference_size>::value_type;

        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            buffer_size,
            std::hardware_destructive_interference_size>
            buffer{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(buffer_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&buffer, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < buffer_size)
                {
                    for (auto&& val : buffer.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        REQUIRE(std::ranges::contains(expected, val));
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == buffer_size);
            });

            std::jthread const producer(
                [&buffer, &produced_count] noexcept -> void {
                    std::this_thread::sleep_for(10ms);

                    for (auto&& val : expected)
                    {
                        std::this_thread::sleep_for(3ms);

                        buffer.emplace_back(val);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == buffer_size);

        REQUIRE(consumed_count == buffer_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(buffer.to_span().size() == buffer_size);

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION(
        "Nondeterministic one producer and one consumer of aggregate values "
        "(delayed producer)"
    )
    {
        using std::chrono::operator""ms;

        static constexpr std::size_t const buffer_size{8};

        using ValueType = dummy_aggregate;

        using SizeType = forfun::concurrency::wait_free::swmr_append_buffer<
            ValueType,
            buffer_size,
            std::hardware_destructive_interference_size>::size_type;

        forfun::concurrency::wait_free::swmr_append_buffer<
            ValueType,
            buffer_size,
            std::hardware_destructive_interference_size>
            buffer{};

        std::vector<ValueType> consumer_bag{};
        consumer_bag.reserve(buffer_size);

        SizeType produced_count{};
        SizeType consumed_count{};

        {
            std::jthread const
            consumer([&buffer, &consumer_bag, &consumed_count] -> void {
                while (consumed_count < buffer_size)
                {
                    for (auto&& val : buffer.to_span().subspan(consumed_count))
                    {
                        consumer_bag.emplace_back(val);
                        ++consumed_count;
                    }
                }

                REQUIRE(consumer_bag.size() == buffer_size);
            });

            std::jthread const producer(
                [&buffer, &produced_count] noexcept -> void {
                    std::this_thread::sleep_for(10ms);

                    for (
                        auto&& n :
                        std::views::iota(1) | std::views::take(buffer_size)
                    )
                    {
                        std::this_thread::sleep_for(10ms);

                        buffer.emplace_back(n * 111, n * 4, n * 8, n * 20);
                        ++produced_count;
                    }
                }
            );
        }

        REQUIRE(produced_count == buffer_size);

        REQUIRE(consumed_count == buffer_size);

        REQUIRE(produced_count == consumed_count);

        REQUIRE(consumer_bag.size() == consumed_count);

        REQUIRE(buffer.to_span().size() == buffer_size);

        int generator_state{1};
        std::array<ValueType, buffer_size> expected{};
        for (auto& val : expected)
        {
            auto const n{generator_state++};
            val = {.a = n * 111, .b = n * 4, .c = n * 8, .d = n * 20};
        }

        REQUIRE_THAT(consumer_bag, Catch::Matchers::RangeEquals(expected));
    }

    SECTION("Benchmark case")
    {
        constexpr std::size_t const capacity{16};

        // NOLINTNEXTLINE(cppcoreguidelines-init-variables)
        int volatile val /*[[indeterminate]]*/;
        forfun::concurrency::wait_free::swmr_append_buffer<
            int,
            capacity,
            std::hardware_destructive_interference_size>
            buffer{};

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        buffer.emplace_back(502807);
        val = buffer.to_span().back();

        REQUIRE(val == 502807);
    }
}
