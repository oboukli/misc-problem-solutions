// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_FORWARD_LIST_NODE_HPP_
#define FORFUN_CONTAINER_FORWARD_LIST_NODE_HPP_

#include <concepts>

namespace forfun::experimental::container {

template <typename T>
    requires std::integral<T>
struct [[nodiscard]] forward_list_node final {
    forward_list_node* next_{};

    T value_{};

    explicit constexpr forward_list_node(T value) noexcept : value_{value}
    {
    }

    explicit constexpr forward_list_node(
        T value, forward_list_node* node
    ) noexcept :
        next_{node}, value_{value}
    {
    }

    forward_list_node(forward_list_node const&) noexcept = delete;

    forward_list_node(forward_list_node&&) noexcept = delete;

    ~forward_list_node() noexcept = default;

    auto operator=(forward_list_node const&) noexcept
        -> forward_list_node& = delete;

    auto operator=(forward_list_node&&) noexcept -> forward_list_node& = delete;
};

} // namespace forfun::experimental::container

#endif // FORFUN_CONTAINER_FORWARD_LIST_NODE_HPP_
