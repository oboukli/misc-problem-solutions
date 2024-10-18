// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_FORWARD_LIST_NODE_HPP_
#define FORFUN_CONTAINER_INTERNAL_FORWARD_LIST_NODE_HPP_

#include <concepts>

namespace forfun::experimental::container::internal {

template <std::integral T>
struct forward_list_node final {
    forward_list_node* next{nullptr};

    T value{};

    explicit constexpr forward_list_node(T val) noexcept : value{val}
    {
    }

    explicit constexpr forward_list_node(
        T val, forward_list_node* node
    ) noexcept :
        next{node}, value{val}
    {
    }

    forward_list_node(forward_list_node const&) = delete;

    auto operator=(forward_list_node const&) -> forward_list_node& = delete;

    forward_list_node(forward_list_node&&) = delete;

    auto operator=(forward_list_node&&) -> forward_list_node& = delete;

    ~forward_list_node() = default;
};

} // namespace forfun::experimental::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_FORWARD_LIST_NODE_HPP_
