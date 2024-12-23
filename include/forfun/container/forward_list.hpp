// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Linked_list

#ifndef FORFUN_CONTAINER_FORWARD_LIST_HPP_
#define FORFUN_CONTAINER_FORWARD_LIST_HPP_

#include <concepts>
#include <utility>

#include "forfun/container/internal/forward_list_node.hpp"

namespace forfun::experimental::container {

template <std::integral T>
class forward_list final {
public:
    using value_type = T;

    using reference = T&;

    forward_list() noexcept = default;

    forward_list(forward_list<T> const&) = delete;

    forward_list(forward_list<T>&&) = delete;

    ~forward_list() noexcept
    {
        clear();
    }

    auto operator=(forward_list<T> const&) -> forward_list& = delete;

    auto operator=(forward_list<T>&&) -> forward_list& = delete;

    [[nodiscard]] auto front() const noexcept -> reference
    {
        return head_->value;
    }

    [[nodiscard]] auto empty() const noexcept -> bool
    {
        return head_ == nullptr;
    }

    auto push_front(T&& value) -> void
    {
        internal::forward_list_node<T>* const aux{head_};

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        head_ = new internal::forward_list_node<T>(std::move(value));

        head_->next = aux;
    }

    auto pop_front() noexcept -> void
    {
        if (head_ == nullptr)
        {
            return;
        }

        internal::forward_list_node<T>* const aux{head_};
        head_ = head_->next;

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        delete aux;
    }

    auto clear() noexcept -> void
    {
        for (internal::forward_list_node<T>* node{head_}; node != nullptr;)
        {
            internal::forward_list_node<T>* const next = node->next;

            // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
            delete node;

            node = next;
        }

        head_ = nullptr;
    }

private:
    internal::forward_list_node<T>* head_;
};

} // namespace forfun::experimental::container

#endif // FORFUN_CONTAINER_FORWARD_LIST_HPP_
