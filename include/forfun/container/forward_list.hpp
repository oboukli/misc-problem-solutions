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

#include "forfun/container/forward_list_node.hpp"

namespace forfun::experimental::container {

template <std::integral T>
class forward_list final {
public:
    using value_type = T;

    using reference = value_type&;

    using const_reference = value_type const&;

    constexpr forward_list() noexcept = default;

    forward_list(forward_list const&) noexcept = delete;

    forward_list(forward_list&&) noexcept = delete;

    constexpr ~forward_list() noexcept
    {
        clear();
    }

    auto operator=(forward_list const&) noexcept -> forward_list& = delete;

    auto operator=(forward_list&&) noexcept -> forward_list& = delete;

    [[nodiscard]] constexpr auto front() noexcept -> reference
    {
        return head_->value_;
    }

    [[nodiscard]] constexpr auto front() const noexcept -> const_reference
    {
        return head_->value_;
    }

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return head_ == nullptr;
    }

    auto push_front(T&& value) -> void
    {
        forfun::container::forward_list_node<T>* const aux{head_};

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        head_ = new forfun::container::forward_list_node<T>{std::move(value)};

        head_->next_ = aux;
    }

    /// @note The behavior is undefined when popping the front of an empty
    /// container.
    auto pop_front() noexcept -> void
    {
        assert(head_ != nullptr);

        forfun::container::forward_list_node<T> const* const aux{head_};
        head_ = head_->next_;

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        delete aux;
    }

    constexpr auto clear() noexcept -> void
    {
        // clang-format off
        for (forfun::container::forward_list_node<T> const* node{head_};
            node != nullptr;)
        // clang-format on
        {
            forfun::container::forward_list_node<T> const* const next{
                node->next_
            };

            // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
            delete node;

            node = next;
        }

        head_ = nullptr;
    }

    constexpr auto reverse() noexcept -> void
    {
        forfun::container::forward_list_node<T>* prev{nullptr};
        forfun::container::forward_list_node<T>* node{head_};

        while (node != nullptr)
        {
            forfun::container::forward_list_node<T>* next{node->next_};

            node->next_ = prev;

            prev = node;
            node = next;
        }

        head_ = prev;
    }

private:
    forfun::container::forward_list_node<T>* head_;
};

} // namespace forfun::experimental::container

#endif // FORFUN_CONTAINER_FORWARD_LIST_HPP_
