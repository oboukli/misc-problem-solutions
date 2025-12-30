// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_NODE_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_NODE_HPP_

namespace forfun::experimental::container::internal {

class list_node final {
public:
    using value_type = int;

    list_node* previous_{};

    list_node* next_{};

    value_type value_{};

    explicit constexpr list_node() noexcept = default;

    explicit constexpr list_node(
        value_type const value,
        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        list_node* previous_node,
        list_node* next_node
    ) noexcept :
        previous_{previous_node}, next_{next_node}, value_{value}
    {
    }

    list_node(list_node const&) noexcept = delete;

    list_node(list_node&&) noexcept = delete;

    constexpr ~list_node() noexcept = default;

    auto operator=(list_node const&) noexcept -> list_node& = delete;

    auto operator=(list_node&&) noexcept -> list_node& = delete;
};

} // namespace forfun::experimental::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_LIST_NODE_HPP_
