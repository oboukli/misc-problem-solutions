// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_LIST_ITERATOR_HPP_
#define FORFUN_CONTAINER_LIST_ITERATOR_HPP_

#include <iterator>

#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container {

class list_iterator final {
public:
    using iterator_category = std::forward_iterator_tag;
    using pointer = list_node*;
    using reference = int&;
    using value_type = int;

    constexpr explicit list_iterator(list_node* const node) noexcept :
        node_{node}
    {
    }

    constexpr list_iterator(list_iterator const& other) noexcept = default;

    auto operator=(list_iterator const& other
    ) noexcept -> list_iterator& = default;

    constexpr list_iterator(list_iterator&& other) noexcept : node_{other.node_}
    {
        other.node_ = nullptr;
    }

    auto operator=(list_iterator&& other) noexcept -> list_iterator&
    {
        node_ = other.node_;
        other.node_ = nullptr;
        return *this;
    }

    constexpr ~list_iterator() noexcept = default;

    auto operator*() const noexcept -> reference
    {
        return node_->value_;
    }

    auto operator++() noexcept -> list_node*
    {
        node_ = node_->next_;
        return node_;
    }

    auto operator++(int) noexcept -> list_node*
    {
        auto* const aux{node_};
        ++*this;
        return aux;
    }

    auto operator==(list_iterator const& other) const noexcept -> bool
    {
        return node_ == other.node_;
    }

    auto operator!=(list_iterator const& other) const noexcept -> bool
    {
        return node_ != other.node_;
    }

private:
    list_node* node_;
};

} // namespace forfun::experimental::container

template <>
struct std::iterator_traits<forfun::experimental::container::list_iterator> {
    using iterator_category
        = forfun::experimental::container::list_iterator::iterator_category;
    using reference = forfun::experimental::container::list_iterator::reference;
    using pointer = forfun::experimental::container::list_iterator::pointer;
    using value_type
        = forfun::experimental::container::list_iterator::value_type;
};

#endif // FORFUN_CONTAINER_LIST_ITERATOR_HPP_