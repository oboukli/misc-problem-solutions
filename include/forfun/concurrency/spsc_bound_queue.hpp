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
#include <execution>
#include <iterator>
#include <memory>
#include <new>
#include <span>
#include <utility>

namespace forfun::concurrency::wait_free {

namespace detail {

/// @note Assumes @p buffer is correctly aligned.
template <typename Pointer, typename Offset>
[[nodiscard]] constexpr auto
get_ptr_to_obj(std::byte* const buffer, Offset const offset) noexcept -> Pointer
{
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif // defined(__GNUC__) && !defined(__clang__)

    assert(
        reinterpret_cast<std::uintptr_t>(
            reinterpret_cast<Pointer>(buffer) + offset
        ) % alignof(std::remove_pointer_t<Pointer>)
        == 0UZ
    );

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
    return reinterpret_cast<Pointer>(buffer) + offset;

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__) && !defined(__clang__)
}

/// @note Assumes @p buffer is correctly aligned.
template <typename Pointer>
[[nodiscard]] constexpr auto get_ptr_to_obj(std::byte* const buffer) noexcept
    -> Pointer
{
    return get_ptr_to_obj<Pointer>(buffer, std::ptrdiff_t{});
}

using std::destroy_n;

template <typename Pointer, typename Size>
auto constexpr destroy_n(std::byte* const buffer, Size n) noexcept(noexcept(
#if defined(__cpp_lib_execution) && __cpp_lib_execution >= 201603L
    destroy_n(
        std::execution::unseq, std::declval<Pointer>(), std::declval<Size>()
    )
#else
    destroy_n(std::declval<Pointer>(), std::declval<Size>())
#endif // defined(__cpp_lib_execution) && __cpp_lib_execution >= 201603L
)) -> std::byte*
{
    using std::data;

    auto* const ptr{get_ptr_to_obj<Pointer>(buffer)};

#if defined(__cpp_lib_execution) && __cpp_lib_execution >= 201603L
    return destroy_n(std::execution::unseq, ptr, n);
#else
    return destroy_n(ptr, n);
#endif // defined(__cpp_lib_execution) && __cpp_lib_execution >= 201603L
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
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,hicpp-member-init)
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

    spsc_bound_queue() = default;

#ifdef _MSC_VER
#pragma warning(pop) // C26495
#endif // _MSC_VER

    spsc_bound_queue(spsc_bound_queue const&) = delete;

    spsc_bound_queue(spsc_bound_queue&&) = delete;

    constexpr ~spsc_bound_queue() noexcept(noexcept(detail::destroy_n(
        std::declval<typename raw_queue_type::pointer>(), capacity_
    )))
    {
        using std::data;

        if (write_cursor_cached_ == cursor_type{0})
        {
            return;
        }

        assert(write_cursor_cached_ <= static_cast<cursor_type>(capacity_));

        detail::destroy_n(data(raw_queue_), write_cursor_cached_);
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
            == cursor_type{0};
    }

    /// @note Undefined behavior when pushing to a full container.
    template <typename... Args>
    auto emplace_back(Args&&... args) noexcept -> reference
    {
        using std::atomic_fetch_add_explicit;
        using std::atomic_load_explicit;
        using std::data;

        static_assert(capacity_ != 0UZ);

        assert(write_cursor_cached_ < static_cast<cursor_type>(capacity_));

        auto* const ptr_emplaced{std::construct_at(
            detail::get_ptr_to_obj<pointer>(
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

    [[nodiscard]] auto to_span() noexcept -> span_type
    {
        using std::atomic_load_explicit;
        using std::data;

        auto const cursor_snapshot{
            atomic_load_explicit(&write_cursor_, std::memory_order_acquire)
        };

        return span_type(
            detail::get_ptr_to_obj<pointer>(data(raw_queue_)),
            static_cast<size_type>(cursor_snapshot)
        );
    }

    [[nodiscard]] static consteval auto capacity() noexcept -> size_type
    {
        return capacity_;
    }

private:
    static_assert(std::has_single_bit(Capacity));
    static constexpr std::size_t const capacity_{Capacity};

    /// Raw cursor type, without atomic wrapper.
    using cursor_type = std::ptrdiff_t;

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

    cursor_type write_cursor_cached_{0};

    static_assert(
        std::hardware_destructive_interference_size >= sizeof(cursor_type)
    );

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif // defined(__GNUC__) && !defined(__clang__)

    std::array<
        std::byte,
        std::hardware_destructive_interference_size - sizeof(cursor_type)>
        end_of_object_padding_ /*[[indeterminate]]*/;
};

} // namespace forfun::concurrency::wait_free

#endif // FORFUN_CONCURRENCY_SPSC_APPEND_QUEUE_HPP_
