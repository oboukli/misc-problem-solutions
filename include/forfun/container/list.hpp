// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Linked_list

#ifndef FORFUN_CONTAINER_LIST_HPP_
#define FORFUN_CONTAINER_LIST_HPP_

#include <cstddef>

#include <gsl/pointers>

#include "forfun/container/internal/list_const_iterator.hpp"
#include "forfun/container/internal/list_iterator.hpp"
#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container {

class list final {
public:
    using value_type = int;

    using size_type = std::size_t;

    using reference = value_type&;

    using const_reference = value_type const&;

    using iterator = internal::list_iterator;

    using const_iterator = internal::list_const_iterator;

    explicit list() : end_{new internal::list_node()}
    {
        head_ = end_;
        tail_ = end_;
    }

    list(list const&) = delete;

    list(list&&) noexcept = delete;

    ~list() noexcept
    {
        clear();

        delete end_;
    }

    auto operator=(list const&) -> list& = delete;

    auto operator=(list&&) noexcept -> list& = delete;

    [[nodiscard]] constexpr auto size() const noexcept -> size_type
    {
        return size_;
    }

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return size_ == size_type{};
    }

    [[nodiscard]] auto front() noexcept -> reference
    {
        return head_->value_;
    }

    [[nodiscard]] auto front() const noexcept -> const_reference
    {
        return head_->value_;
    }

    [[nodiscard]] auto back() const noexcept -> value_type
    {
        return tail_->value_;
    }

    auto push_back(value_type value) -> void;

    auto pop_back() noexcept -> void;

    auto clear() noexcept -> void;

    [[nodiscard]] auto begin() const noexcept -> iterator;

    [[nodiscard]] auto end() const noexcept -> iterator;

    [[nodiscard]] auto cbegin() const noexcept -> const_iterator;

    [[nodiscard]] auto cend() const noexcept -> const_iterator;

private:
    internal::list_node* head_;
    internal::list_node* tail_;
    gsl::owner<internal::list_node*> end_;
    size_type size_{};
};

} // namespace forfun::experimental::container

#endif // FORFUN_CONTAINER_LIST_HPP_
