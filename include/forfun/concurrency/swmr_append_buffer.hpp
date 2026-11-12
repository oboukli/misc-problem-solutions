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

#include <forfun/common/type_traits.hpp>

namespace forfun::concurrency::wait_free {

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

    using const_reference
        = std::add_lvalue_reference_t<std::add_const_t<value_type>>;

    using span_type = std::span<std::add_const_t<value_type>>;

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init,modernize-use-equals-default)
    swmr_append_buffer() noexcept
    {
        // Avoid zero initialization.
    }

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
    auto emplace_back(Args&&... args) noexcept -> const_reference
    {
        using std::atomic_load_explicit;
        using std::atomic_store_explicit;

        auto const write_cursor_copy{
            atomic_load_explicit(&write_cursor_, std::memory_order_relaxed)
        };

        assert(std::cmp_less(write_cursor_copy, capacity_));

        auto const* const ptr_emplaced{std::construct_at(
            to_pointer(static_cast<std::size_t>(write_cursor_copy)),
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

    [[nodiscard]] auto to_span() const noexcept -> span_type
    {
        using std::atomic_load_explicit;

        auto const last{
            atomic_load_explicit(&write_cursor_, std::memory_order_acquire)
        };

        return span_type(to_pointer(0UZ), static_cast<size_type>(last));
    }

    [[nodiscard]] static constexpr auto capacity() noexcept -> size_type
    {
        return capacity_;
    }

private:
    static constexpr std::size_t const capacity_{Size};

    using const_pointer = std::add_pointer_t<std::add_const_t<value_type>>;

    using pointer = std::add_pointer_t<value_type>;

    /// Raw cursor type, without atomic wrapper.
    using cursor_type = std::size_t;

    static_assert(std::atomic<cursor_type>::is_always_lock_free);

    alignas(Type) storage_type storage_;

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

    [[nodiscard]] auto
    to_pointer(this auto& self, std::size_t const offset) noexcept -> forfun::
        common::type_traits::if_const_t<decltype(self), const_pointer, pointer>
    {
        using IntermediatePointer = forfun::common::type_traits::
            if_const_t<decltype(self), void const*, void*>;

        using Pointer = forfun::common::type_traits::
            if_const_t<decltype(self), const_pointer, pointer>;

        return static_cast<Pointer>(static_cast<IntermediatePointer>(
            // NOLINTNEXTLINE(bugprone-casting-through-void,cppcoreguidelines-pro-bounds-pointer-arithmetic)
            std::data(self.storage_) + (offset * sizeof(value_type))
        ));
    }

    auto reset_storage() noexcept -> void
    {
        using std::atomic_load_explicit;

        auto const write_cursor_copy{
            atomic_load_explicit(&write_cursor_, std::memory_order_relaxed)
        };

        assert(std::cmp_less_equal(write_cursor_copy, capacity_));

        if constexpr (not std::is_trivially_destructible_v<value_type>)
        {
            auto const size{static_cast<size_type>(write_cursor_copy)};
            auto* reversed_first{
                to_pointer(static_cast<size_type>(write_cursor_copy))
            };
            for (auto i{size}; i != size_type{}; --i)
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                std::destroy_at(reversed_first + (i - size_type{1}));
            }
        }
    }
};

} // namespace forfun::concurrency::wait_free

#endif // FORFUN_CONCURRENCY_SWMR_APPEND_BUFFER_HPP_
