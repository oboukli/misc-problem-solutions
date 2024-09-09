// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HELPER_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HELPER_HPP_

#include <cstddef>
#include <iterator>

#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container::internal {

template <typename T>
class list_iterator_helper {
public:
    using const_reference = int const&;

    using difference_type = std::ptrdiff_t;

    using iterator_category = std::bidirectional_iterator_tag;

    using iterator_concept = std::bidirectional_iterator_tag;

    using pointer = T;

    using value_type = int;

private:
    constexpr explicit list_iterator_helper() noexcept : node_{}
    {
    }

    constexpr explicit list_iterator_helper(list_node* const node) noexcept :
        node_{node}
    {
    }

    constexpr list_iterator_helper(list_iterator_helper const& other) noexcept
        = default;

    constexpr list_iterator_helper(list_iterator_helper&& other) noexcept :
        node_{other.node_}
    {
        other.node_ = nullptr;
    }

public:
    constexpr ~list_iterator_helper() noexcept = default;

    auto operator=(list_iterator_helper const& other) noexcept
        -> list_iterator_helper& = default;

    auto operator=(list_iterator_helper&& other) noexcept
        -> list_iterator_helper&
    {
        node_ = other.node_;
        other.node_ = nullptr;
        return *this;
    }

    auto operator++() noexcept -> T&
    {
        node_ = node_->next_;
        return *static_cast<T*>(this);
    }

    auto operator++(int) noexcept -> T
    {
        auto const aux{*static_cast<T*>(this)};
        ++*this;
        return aux;
    }

    auto operator--() noexcept -> T&
    {
        node_ = node_->previous_;
        return *static_cast<T*>(this);
    }

    auto operator--(int) noexcept -> T
    {
        auto const aux{*static_cast<T*>(this)};
        node_ = node_->previous_;
        return aux;
    }

    auto operator==(T const& other) const noexcept -> bool
    {
        return node_ == other.node_;
    }

    auto operator==(std::default_sentinel_t const& /*unused*/) const -> bool
    {
        return node_->next_ == nullptr;
    }

    auto operator!=(T const& other) const noexcept -> bool
    {
        return node_ != other.node_;
    }

    auto operator!=(std::default_sentinel_t const& /*unused*/) const -> bool
    {
        return node_->next_ != nullptr;
    }

private:
    list_node* node_;
    friend T;
};

} // namespace forfun::experimental::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HELPER_HPP_
