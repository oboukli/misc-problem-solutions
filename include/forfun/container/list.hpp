// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Linked_list

#ifndef FORFUN_CONTAINER_LIST_HPP_
#define FORFUN_CONTAINER_LIST_HPP_

#include <cstddef>

#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container {

class list final {
public:
    using size_type = std::size_t;
    using value_type = int;

    constexpr list() noexcept = default;

    constexpr list(list const&) noexcept = delete;

    auto operator=(list const&) noexcept -> list& = delete;

    constexpr list(list&&) noexcept = delete;

    auto operator=(list&&) noexcept -> list& = delete;

    ~list() noexcept
    {
        clear();
    }

    [[nodiscard]] constexpr auto size() const noexcept -> size_type
    {
        return size_;
    }

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return size_ == size_type{};
    }

    [[nodiscard]] auto front() const noexcept -> value_type
    {
        return head_->value_;
    }

    [[nodiscard]] auto back() const noexcept -> value_type
    {
        return tail_->value_;
    }

    auto push_back(value_type value) noexcept -> void;

    auto pop_back() noexcept -> void;

    auto clear() noexcept -> void;

private:
    list_node* head_{nullptr};
    list_node* tail_{nullptr};
    size_type size_{};
};

} // namespace forfun::experimental::container

#endif // FORFUN_CONTAINER_LIST_HPP_
