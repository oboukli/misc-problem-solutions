// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Linked_list

#ifndef FORFUN_CONTAINER_FORWARD_LIST_HPP_
#define FORFUN_CONTAINER_FORWARD_LIST_HPP_

#include <cassert>
#include <concepts>
#include <utility>

#include "forfun/container/internal/forward_list_node.hpp"

namespace forfun::experimental::container {

template <std::integral T>
class forward_list final {
public:
    using value_type = T;

    using reference = value_type&;

    using const_reference = value_type const&;

    constexpr forward_list() noexcept = default;

    forward_list(forward_list const&) = delete;

    forward_list(forward_list&&) = delete;

    constexpr ~forward_list() noexcept
    {
        clear();
    }

    auto operator=(forward_list const&) -> forward_list& = delete;

    auto operator=(forward_list&&) -> forward_list& = delete;

    [[nodiscard]] constexpr auto front() noexcept -> reference
    {
        return head_->value;
    }

    [[nodiscard]] constexpr auto front() const noexcept -> const_reference
    {
        return head_->value;
    }

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return head_ == nullptr;
    }

    auto push_front(T&& value) -> void
    {
        internal::forward_list_node<T>* const aux{head_};

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        head_ = new internal::forward_list_node<T>{std::move(value)};

        head_->next = aux;
    }

    /// @note The behavior is undefined when popping the front of an empty
    /// container.
    auto pop_front() noexcept -> void
    {
        assert(head_ != nullptr);

        internal::forward_list_node<T> const* const aux{head_};
        head_ = head_->next;

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        delete aux;
    }

    constexpr auto clear() noexcept -> void
    {
        // clang-format off
        for (internal::forward_list_node<T> const* node{head_};
            node != nullptr;)
        // clang-format on
        {
            internal::forward_list_node<T> const* const next{node->next};

            // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
            delete node;

            node = next;
        }

        head_ = nullptr;
    }

    constexpr auto reverse() noexcept -> void
    {
        internal::forward_list_node<T>* prev{nullptr};
        internal::forward_list_node<T>* node{head_};

        while (node != nullptr)
        {
            internal::forward_list_node<T>* next{node->next};

            node->next = prev;

            prev = node;
            node = next;
        }

        head_ = prev;
    }

private:
    internal::forward_list_node<T>* head_;
};

} // namespace forfun::experimental::container

#endif // FORFUN_CONTAINER_FORWARD_LIST_HPP_
