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

template <typename Derived>
class list_iterator_helper {
public:
    using difference_type = std::ptrdiff_t;

    using pointer = Derived;

    using iterator_category = std::bidirectional_iterator_tag;

    using iterator_concept = std::bidirectional_iterator_tag;

    constexpr ~list_iterator_helper() noexcept = default;

    auto operator=(list_iterator_helper const& other) noexcept
        -> list_iterator_helper& = default;

    auto operator=(list_iterator_helper&& other) noexcept
        -> list_iterator_helper& = default;

    auto operator++(this auto&& self) noexcept -> Derived&
    {
        self.node_ = self.node_->next_;

        return self;
    }

    [[nodiscard]] auto operator++(this auto&& self, int) noexcept -> Derived
    {
        auto aux{self};
        ++self;

        return aux;
    }

    auto operator--(this auto&& self) noexcept -> Derived&
    {
        self.node_ = self.node_->previous_;

        return self;
    }

    [[nodiscard]] auto operator--(this auto&& self, int) noexcept -> Derived
    {
        auto aux{self};
        self.node_ = self.node_->previous_;

        return aux;
    }

    auto operator==(Derived const& other) const noexcept -> bool
    {
        return node_ == other.node_;
    }

    auto operator==(std::default_sentinel_t const& /*unused*/) const noexcept
        -> bool
    {
        return node_->next_ == nullptr;
    }

    auto operator!=(Derived const& other) const noexcept -> bool
    {
        return node_ != other.node_;
    }

    auto operator!=(std::default_sentinel_t const& /*unused*/) const noexcept
        -> bool
    {
        return node_->next_ != nullptr;
    }

private:
    list_node* node_{};

    friend Derived;

    constexpr explicit list_iterator_helper() noexcept = default;

    constexpr explicit list_iterator_helper(list_node* const node) noexcept :
        node_{node}
    {
    }

    constexpr list_iterator_helper(list_iterator_helper const& other) noexcept
        = default;

    constexpr list_iterator_helper(list_iterator_helper&& other) noexcept
        = default;
};

} // namespace forfun::experimental::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HELPER_HPP_
