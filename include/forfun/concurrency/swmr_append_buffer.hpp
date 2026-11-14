// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONCURRENCY_SWMR_APPEND_BUFFER_HPP_
#define FORFUN_CONCURRENCY_SWMR_APPEND_BUFFER_HPP_

#include <array>
#include <atomic>
#include <bit>
#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <memory>
#include <span>
#include <type_traits>
#include <utility>

namespace forfun::concurrency::wait_free {

namespace detail {

/// @note Assumes @p buffer is correctly aligned.
template <typename Type>
[[nodiscard]] constexpr auto
get_ptr_to_obj(std::byte* const buffer, std::size_t const offset) noexcept
    -> Type*
{
    // NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
    assert(reinterpret_cast<std::uintptr_t>(buffer) % alignof(Type) == 0UZ);

    assert(((offset * sizeof(Type)) % alignof(Type)) == 0UZ);

    return reinterpret_cast<Type*>(buffer + (offset * sizeof(Type)));
    // NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast,cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

} // namespace detail

/// Single-writer multiple non-claiming readers, bounded append-only buffer.
///
/// Features:
/// - Wait-free (lock-free) concurrency model
/// - Fixed-capacity, and non-circular
/// - Multi-pass reads via @c std::span
/// - Inline storage with no dynamic allocation
/// - Append-one by one; Reset all, manually or when buffer is destroyed.
///
/// @warning Experimental implementation. Has not been reviewed for safety or
/// security.
template <typename Type, std::size_t Size, std::size_t CacheLineSeparation>
    requires std::is_object_v<Type>
    and std::same_as<Type, std::remove_cv_t<Type>>
    and (not std::is_array_v<Type>)
    and std::destructible<Type>
    and (Size > 0UZ)
    // NOLINTNEXTLINE(readability-redundant-parentheses)
    and (std::cmp_less_equal(
        Size, std::numeric_limits<std::size_t>::max() / sizeof(Type)
    ))
    // NOLINTNEXTLINE(readability-redundant-parentheses)
    and (std::cmp_less_equal(Size, std::numeric_limits<std::ptrdiff_t>::max()))
    // NOLINTNEXTLINE(readability-redundant-parentheses)
    and (std::has_single_bit(CacheLineSeparation))
    and (CacheLineSeparation >= alignof(std::atomic<std::size_t>))
// NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,clang-analyzer-optin.performance.Padding)
class swmr_append_buffer final {
private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,modernize-avoid-c-arrays)
    using storage_type = std::byte[Size * sizeof(Type)];

public:
    using size_type = std::size_t;

    using value_type = Type;

    using reference = value_type&;

    using span_type = std::span<value_type>;

#ifdef _MSC_VER
#pragma warning(push)
// Warning C26495: Variable 'variable' is uninitialized. Always initialize a
// member variable (type.6).
#pragma warning(disable : 26495)
#endif // _MSC_VER

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    swmr_append_buffer() noexcept
    {
        // Avoid zero initialization.
    }

#ifdef _MSC_VER
#pragma warning(pop) // C26495
#endif // _MSC_VER

    swmr_append_buffer(swmr_append_buffer const&) = delete;

    swmr_append_buffer(swmr_append_buffer&&) = delete;

    ~swmr_append_buffer()
        requires std::is_trivially_destructible_v<value_type>
    = default;

    ~swmr_append_buffer()
        requires(not std::is_trivially_destructible_v<value_type>)
    {
        reset_storage();
    }

    auto operator=(swmr_append_buffer const&) -> swmr_append_buffer& = delete;

    auto operator=(swmr_append_buffer&&) -> swmr_append_buffer& = delete;

    [[nodiscard]] auto empty() const noexcept -> bool
    {
        using std::atomic_load_explicit;

        return atomic_load_explicit(&write_cursor_, std::memory_order_relaxed)
            == cursor_type{};
    }

    /// @note Undefined behavior when pushing to a full container.
    template <typename... Args>
    auto emplace_back(Args&&... args) noexcept -> reference
    {
        using std::atomic_load_explicit;
        using std::atomic_store_explicit;

        auto const write_cursor_copy{
            atomic_load_explicit(&write_cursor_, std::memory_order_relaxed)
        };

        assert(std::cmp_less(write_cursor_copy, capacity_));

        auto* const ptr_emplaced{std::construct_at(
            detail::get_ptr_to_obj<value_type>(
                std::data(raw_queue_), write_cursor_copy
            ),
            std::forward<Args>(args)...
        )};

        atomic_store_explicit(
            &write_cursor_,
            write_cursor_copy + cursor_type{1},
            std::memory_order_release
        );

        return *ptr_emplaced;
    }

    auto reset_unsafe() noexcept -> void
    {
        using std::atomic_store_explicit;

        reset_storage();

        atomic_store_explicit(
            &write_cursor_, cursor_type{}, std::memory_order_release
        );
    }

    [[nodiscard]] auto to_span() noexcept -> span_type
    {
        using std::atomic_load_explicit;

        auto const last{
            atomic_load_explicit(&write_cursor_, std::memory_order_acquire)
        };

        return span_type(
            detail::get_ptr_to_obj<value_type>(std::data(raw_queue_), {}),
            static_cast<size_type>(last)
        );
    }

    [[nodiscard]] static constexpr auto capacity() noexcept -> size_type
    {
        return capacity_;
    }

private:
    static constexpr std::size_t const capacity_{Size};

    /// Raw cursor type, without atomic wrapper.
    using cursor_type = std::size_t;

    static_assert(std::atomic<cursor_type>::is_always_lock_free);

    alignas(Type) storage_type raw_queue_;

    static_assert(std::same_as<typename span_type::size_type, size_type>);

#ifdef _MSC_VER
#pragma warning(push)
// Warning C4324: 'type': structure was padded due to alignment specifier.
#pragma warning(disable : 4324)
#endif // _MSC_VER

    alignas(CacheLineSeparation) std::atomic<cursor_type> write_cursor_{0};

#ifdef _MSC_VER
#pragma warning(pop) // C4324
#endif // _MSC_VER

    static_assert(CacheLineSeparation >= sizeof(cursor_type));

    std::array<std::byte, CacheLineSeparation - sizeof(cursor_type)>
        end_of_object_padding_;

    constexpr auto reset_storage() noexcept -> void
    {
        using std::atomic_load_explicit;

        auto const write_cursor_copy{
            atomic_load_explicit(&write_cursor_, std::memory_order_relaxed)
        };

        assert(std::cmp_less_equal(write_cursor_copy, capacity_));

        if constexpr (not std::is_trivially_destructible_v<value_type>)
        {
            auto const size{static_cast<size_type>(write_cursor_copy)};
            auto* reversed_first{detail::get_ptr_to_obj<value_type>(
                std::data(raw_queue_), static_cast<size_type>(write_cursor_copy)
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
