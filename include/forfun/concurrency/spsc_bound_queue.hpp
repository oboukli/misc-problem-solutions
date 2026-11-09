// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONCURRENCY_SPSC_APPEND_QUEUE_HPP_
#define FORFUN_CONCURRENCY_SPSC_APPEND_QUEUE_HPP_

#include <array>
#include <atomic>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <memory>
#include <new>
#include <span>
#include <utility>

namespace forfun::concurrency::wait_free {

namespace detail {

/// @note Assumes @p buffer is correctly aligned.
template <typename Type>
[[nodiscard]] constexpr auto
get_ptr_to_obj(std::byte* const buffer, std::size_t const offset) noexcept
    -> Type*
{
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif // defined(__GNUC__) && !defined(__clang__)

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
#endif // __clang__

    // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
    assert(reinterpret_cast<std::uintptr_t>(buffer) % alignof(Type) == 0UZ);

    assert(((offset * sizeof(Type)) % alignof(Type)) == 0UZ);

    return reinterpret_cast<Type*>(buffer + (offset * sizeof(Type)));
    // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__) && !defined(__clang__)
}

} // namespace detail

/// Single-producer single-consumer (SPSC) bound queue.
///
/// Features:
/// - Wait-free (lock-free) concurrency model
/// - First in, first out (FIFO) order semantics
/// - Multi-pass reads via \c std::span
/// - Bounded, fixed-capacity, and non-circular
/// - Inline storage with no dynamic allocation
/// - Append-only; elements are deconstructed when the queue is deconstructed.
///
/// @note The implementation prioritizes performance over safety and security.
///
/// @note Internal storage and padding area might not be (zero-)initialized.
template <typename T, std::size_t Capacity>
    requires std::destructible<T>
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,clang-analyzer-optin.performance.Padding)
class spsc_bound_queue final {
private:
    using pointer = T*;

    using raw_queue_type = std::array<std::byte, Capacity * sizeof(T)>;

public:
    using size_type = std::size_t;

    using value_type = T;

    using reference = value_type&;

    using span_type = std::span<value_type>;

#ifdef _MSC_VER
#pragma warning(push)
// Warning C26495: Variable 'variable' is uninitialized. Always initialize a
// member variable (type.6).
#pragma warning(disable : 26495)
#endif // _MSC_VER

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    spsc_bound_queue() = default;

#ifdef _MSC_VER
#pragma warning(pop) // C26495
#endif // _MSC_VER

    spsc_bound_queue(spsc_bound_queue const&) = delete;

    spsc_bound_queue(spsc_bound_queue&&) = delete;

    ~spsc_bound_queue()
        requires(std::is_trivially_destructible_v<value_type>)
    = default;

    ~spsc_bound_queue()
        requires(not std::is_trivially_destructible_v<value_type>)
    {
        reset_storage();
    }

    auto operator=(spsc_bound_queue const&) -> spsc_bound_queue& = delete;

    auto operator=(spsc_bound_queue&&) -> spsc_bound_queue& = delete;

    /// @note Padding area might not be (zero-)initialized. Instance-to-instance
    /// comparision is undefined behavior.
    auto operator<=>(spsc_bound_queue const&) const = delete;

    /// @note Not thread-safe.
    [[nodiscard]] auto empty_unsafe() const noexcept -> bool
    {
        using std::atomic_load_explicit;

        return atomic_load_explicit(&write_cursor_, std::memory_order_relaxed)
            == cursor_type{};
    }

    /// @note Undefined behavior when pushing to a full container.
    template <typename... Args>
    auto emplace_back(Args&&... args) noexcept -> reference
    {
        using std::atomic_fetch_add_explicit;
        using std::atomic_load_explicit;
        using std::data;

        static_assert(capacity_ != 0UZ);

        assert(std::cmp_less(write_cursor_cached_, capacity_));

        auto* const ptr_emplaced{std::construct_at(
            detail::get_ptr_to_obj<value_type>(
                data(raw_queue_), write_cursor_cached_
            ),
            std::forward<Args>(args)...
        )};

        ++write_cursor_cached_;
        atomic_store_explicit(
            &write_cursor_, write_cursor_cached_, std::memory_order_release
        );

        return *ptr_emplaced;
    }

    auto reset_unsafe() noexcept -> void
    {
        using std::atomic_store_explicit;

        reset_storage();

        write_cursor_cached_ = {};

        atomic_store_explicit(
            &write_cursor_, cursor_type{}, std::memory_order_release
        );
    }

    [[nodiscard]] auto to_span() noexcept -> span_type
    {
        using std::atomic_load_explicit;
        using std::data;

        auto const cursor_snapshot{
            atomic_load_explicit(&write_cursor_, std::memory_order_acquire)
        };

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage-in-container"
#endif // __clang__

        return span_type(
            detail::get_ptr_to_obj<value_type>(std::data(raw_queue_), {}),
            static_cast<size_type>(cursor_snapshot)
        );

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
    }

    [[nodiscard]] static consteval auto capacity() noexcept -> size_type
    {
        return capacity_;
    }

private:
    static_assert(std::has_single_bit(Capacity));
    static constexpr std::size_t const capacity_{Capacity};

    /// Raw cursor type, without atomic wrapper.
    using cursor_type = std::size_t;

    static_assert(std::atomic<cursor_type>::is_always_lock_free);

    alignas(T) raw_queue_type raw_queue_
        /*[[indeterminate]]*/;

    static_assert(std::same_as<typename raw_queue_type::size_type, size_type>);
    static_assert(std::same_as<typename span_type::size_type, size_type>);

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winterference-size"
#endif // defined(__GNUC__) && !defined(__clang__)

#ifdef _MSC_VER
#pragma warning(push)
// Warning C4324: 'type': structure was padded due to alignment specifier.
#pragma warning(disable : 4324)
#endif // _MSC_VER

    alignas(
        std::hardware_destructive_interference_size
    ) std::atomic<cursor_type> write_cursor_{0};

#ifdef _MSC_VER
#pragma warning(pop) // C4324
#endif // _MSC_VER

    cursor_type write_cursor_cached_{};

    static_assert(
        std::hardware_destructive_interference_size >= sizeof(cursor_type)
    );

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__) && !defined(__clang__)

    std::array<
        std::byte,
        std::hardware_destructive_interference_size - sizeof(cursor_type)>
        end_of_object_padding_;

    constexpr auto reset_storage() noexcept -> void
    {
        assert(std::cmp_less_equal(write_cursor_cached_, capacity_));

        if constexpr (not std::is_trivially_destructible_v<value_type>)
        {
            auto const size{static_cast<size_type>(write_cursor_cached_)};
            auto* reversed_first{detail::get_ptr_to_obj<value_type>(
                std::data(raw_queue_),
                static_cast<size_type>(write_cursor_cached_)
            )};
            for (auto i{size}; i != size_type{}; --i)
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                std::destroy_at(reversed_first + (i - size_type{1}));
            }
        }
    }
};

} // namespace forfun::concurrency::wait_free

#endif // FORFUN_CONCURRENCY_SPSC_APPEND_QUEUE_HPP_
