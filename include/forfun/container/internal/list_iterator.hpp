// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HPP_

#include <cassert>
#include <iterator>

#include "forfun/container/internal/list_iterator_helper.hpp"
#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container::internal {

class list_iterator final : public list_iterator_helper<list_iterator> {
public:
    using value_type = int;

    using reference = value_type&;

    using const_reference = value_type const&;

    constexpr explicit list_iterator() noexcept = default;

    constexpr explicit list_iterator(list_node* const node) noexcept :
        list_iterator_helper{node}
    {
    }

    constexpr list_iterator(list_iterator const& other) noexcept = default;

    constexpr list_iterator(list_iterator&& other) noexcept = default;

    constexpr ~list_iterator() noexcept = default;

    auto operator=(list_iterator const& other) noexcept
        -> list_iterator& = default;

    auto operator=(list_iterator&& other) noexcept -> list_iterator& = default;

    auto operator*() const noexcept -> reference
    {
        assert(node_ != nullptr);

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
