// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_

#include <cassert>
#include <type_traits>

#include "forfun/container/internal/list_bidirectional_iterator_helper.hpp"
#include "forfun/container/internal/list_node.hpp"

namespace forfun::container::internal {

class list_iterator final
    : public list_bidirectional_iterator_helper<list_iterator> {
public:
    using value_type = int;

    using pointer = std::add_pointer_t<value_type>;

    using const_pointer = std::add_pointer_t<std::add_const<value_type>>;

    using reference = std::add_lvalue_reference_t<value_type>;

    using const_reference
        = std::add_lvalue_reference_t<std::add_const_t<value_type>>;

    constexpr list_iterator() noexcept = default;

    constexpr explicit list_iterator(list_node* const node) noexcept :
        list_bidirectional_iterator_helper{node}
    {
    }

    constexpr list_iterator(list_iterator const& other) noexcept = default;

    constexpr list_iterator(list_iterator&& other) noexcept = default;

    ~list_iterator() noexcept = default;

    constexpr auto operator=(list_iterator const& other) noexcept
        -> list_iterator& = default;

    constexpr auto operator=(list_iterator&& other) noexcept
        -> list_iterator& = default;

    constexpr auto operator*() const noexcept -> reference
    {
        assert(node_ != nullptr);

        return node_->value_;
    }

    constexpr auto operator->() const noexcept -> pointer
    {
        assert(node_ != nullptr);

        return &node_->value_;
    }
};

} // namespace forfun::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_
