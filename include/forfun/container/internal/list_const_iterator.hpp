// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_CONST_ITERATOR_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_CONST_ITERATOR_HPP_

#include <cassert>
#include <type_traits>

#include "forfun/container/internal/list_bidirectional_iterator_helper.hpp"
#include "forfun/container/internal/list_node.hpp"

namespace forfun::container::internal {

class list_const_iterator final
    : public list_bidirectional_iterator_helper<list_const_iterator> {
public:
    using value_type = int;

    using const_pointer = std::add_pointer_t<std::add_const_t<value_type>>;

    using pointer = const_pointer;

    using const_reference
        = std::add_lvalue_reference_t<std::add_const_t<value_type>>;

    using reference = const_reference;

    constexpr list_const_iterator() noexcept = default;

    constexpr explicit list_const_iterator(list_node* const node) noexcept :
        list_bidirectional_iterator_helper{node}
    {
    }

    constexpr list_const_iterator(list_const_iterator const&) noexcept
        = default;

    constexpr list_const_iterator(list_const_iterator&&) noexcept = default;

    ~list_const_iterator() noexcept = default;

    constexpr auto operator=(list_const_iterator const&) noexcept
        -> list_const_iterator& = default;

    constexpr auto operator=(list_const_iterator&&) noexcept
        -> list_const_iterator& = default;

    constexpr auto operator*() const noexcept -> const_reference
    {
        assert(node_ != nullptr);

        return node_->value_;
    }
};

} // namespace forfun::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_LIST_CONST_ITERATOR_HPP_
