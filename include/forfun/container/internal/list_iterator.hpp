// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_

#include <iterator>
#include <utility>

#include "forfun/container/internal/list_iterator_helper.hpp"
#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container::internal {

class list_iterator final
    : public internal::list_iterator_helper<list_iterator> {
public:
    using const_reference = int const&;

    using reference = int&;

    constexpr explicit list_iterator() noexcept = default;

    constexpr explicit list_iterator(internal::list_node* const node) noexcept :
        internal::list_iterator_helper<list_iterator>{node}
    {
    }

    constexpr list_iterator(list_iterator const& other) noexcept = default;

    constexpr list_iterator(list_iterator&& other) noexcept :
        internal::list_iterator_helper<list_iterator>(std::move(other))
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

} // namespace forfun::experimental::container::internal

template <>
struct std::iterator_traits<
    forfun::experimental::container::internal::list_iterator> {
    using const_reference = forfun::experimental::container::internal::
        list_iterator::const_reference;

    using difference_type = forfun::experimental::container::internal::
        list_iterator::difference_type;

    using iterator_category = forfun::experimental::container::internal::
        list_iterator::iterator_category;

    using iterator_concept = forfun::experimental::container::internal::
        list_iterator::iterator_concept;

    using pointer
        = forfun::experimental::container::internal::list_iterator::pointer;

    using reference
        = forfun::experimental::container::internal::list_iterator::reference;

    using value_type
        = forfun::experimental::container::internal::list_iterator::value_type;
};

#endif // FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_
