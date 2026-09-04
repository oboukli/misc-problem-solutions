// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_NODE_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_NODE_HPP_

namespace forfun::container::internal {

class list_node final {
public:
    using value_type = int;

    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)

    value_type value_{};

    list_node* previous_{};

    list_node* next_{};

    // NOLINTEND(misc-non-private-member-variables-in-classes)

    constexpr list_node() noexcept = default;

    constexpr list_node(
        value_type const value,
        // NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
        list_node* previous_node,
        list_node* next_node
    ) noexcept :
        value_{value}, previous_{previous_node}, next_{next_node}
    {
    }

    list_node(list_node const&) = delete;

    list_node(list_node&&) = delete;

    constexpr ~list_node() noexcept = default;

    auto operator=(list_node const&) -> list_node& = delete;

    auto operator=(list_node&&) -> list_node& = delete;
};

} // namespace forfun::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_LIST_NODE_HPP_
