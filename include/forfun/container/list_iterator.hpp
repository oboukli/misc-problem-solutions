// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_LIST_ITERATOR_HPP_
#define FORFUN_CONTAINER_LIST_ITERATOR_HPP_

#include <cstddef>
#include <iterator>
#include <utility>

#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container {

namespace detail {

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

} // namespace detail

class list_iterator final : public detail::list_iterator_helper<list_iterator> {
public:
    using const_reference = int const&;

    using reference = int&;

    constexpr explicit list_iterator() noexcept = default;

    constexpr explicit list_iterator(list_node* const node) noexcept :
        detail::list_iterator_helper<list_iterator>{node}
    {
    }

    constexpr list_iterator(list_iterator const& other) noexcept = default;

    constexpr list_iterator(list_iterator&& other) noexcept :
        detail::list_iterator_helper<list_iterator>(std::move(other))
    {
    }

    constexpr ~list_iterator() noexcept = default;

    auto operator=(list_iterator const& other) noexcept
        -> list_iterator& = default;

    auto operator=(list_iterator&& other) noexcept -> list_iterator&
    {
        node_ = other.node_;
        other.node_ = nullptr;
        return *this;
    }

    auto operator*() const noexcept -> reference
    {
        return node_->value_;
    }
};

class list_const_iterator final
    : public detail::list_iterator_helper<list_const_iterator> {
public:
    using const_reference = int const&;

    using reference = const_reference;

    constexpr explicit list_const_iterator() noexcept = default;

    constexpr explicit list_const_iterator(list_node* const node) noexcept :
        detail::list_iterator_helper<list_const_iterator>{node}
    {
    }

    constexpr list_const_iterator(list_const_iterator const& other) noexcept
        = default;

    constexpr list_const_iterator(list_const_iterator&& other) noexcept :
        detail::list_iterator_helper<list_const_iterator>(std::move(other))
    {
    }

    ~list_const_iterator() noexcept = default;

    auto operator=(list_const_iterator const& other) noexcept
        -> list_const_iterator& = default;

    auto operator=(list_const_iterator&& other) noexcept -> list_const_iterator&
    {
        node_ = other.node_;
        other.node_ = nullptr;
        return *this;
    }

    auto operator*() const noexcept -> const_reference
    {
        return node_->value_;
    }
};

} // namespace forfun::experimental::container

template <>
struct std::iterator_traits<forfun::experimental::container::list_iterator> {
    using const_reference
        = forfun::experimental::container::list_iterator::const_reference;

    using difference_type
        = forfun::experimental::container::list_iterator::difference_type;

    using iterator_category
        = forfun::experimental::container::list_iterator::iterator_category;

    using iterator_concept
        = forfun::experimental::container::list_iterator::iterator_concept;

    using pointer = forfun::experimental::container::list_iterator::pointer;

    using reference = forfun::experimental::container::list_iterator::reference;

    using value_type
        = forfun::experimental::container::list_iterator::value_type;
};

template <>
struct std::iterator_traits<
    forfun::experimental::container::list_const_iterator> {
    using const_reference
        = forfun::experimental::container::list_const_iterator::const_reference;

    using difference_type
        = forfun::experimental::container::list_const_iterator::difference_type;

    using iterator_category = forfun::experimental::container::
        list_const_iterator::iterator_category;

    using iterator_concept = forfun::experimental::container::
        list_const_iterator::iterator_concept;

    using pointer
        = forfun::experimental::container::list_const_iterator::pointer;

    using reference
        = forfun::experimental::container::list_const_iterator::reference;

    using value_type
        = forfun::experimental::container::list_const_iterator::value_type;
};

#endif // FORFUN_CONTAINER_LIST_ITERATOR_HPP_
