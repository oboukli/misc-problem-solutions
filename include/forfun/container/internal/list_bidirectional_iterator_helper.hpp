// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HELPER_HPP_
#define FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HELPER_HPP_

#include <cstddef>
#include <iterator>
#include <type_traits>

#include "forfun/container/internal/list_node.hpp"

namespace forfun::container::internal {

template <typename Derived>
class list_bidirectional_iterator_helper {
public:
    using difference_type = std::ptrdiff_t;

    using iterator_category = std::bidirectional_iterator_tag;

    using iterator_concept = std::bidirectional_iterator_tag;

    constexpr ~list_bidirectional_iterator_helper() noexcept = default;

    constexpr auto operator=(list_bidirectional_iterator_helper const&)
        -> list_bidirectional_iterator_helper& = default;

    constexpr auto operator=(list_bidirectional_iterator_helper&&) noexcept
        -> list_bidirectional_iterator_helper& = default;

    constexpr auto operator++(this Derived& self) noexcept -> Derived&
    {
        self.node_ = self.node_->next_;

        return self;
    }

    [[nodiscard]] constexpr auto operator++(
        this Derived& self, int
    ) noexcept(std::is_nothrow_copy_constructible_v<Derived>) -> Derived
    {
        auto aux{self};
        ++self;

        return aux;
    }

    constexpr auto operator--(this Derived& self) noexcept -> Derived&
    {
        self.node_ = self.node_->previous_;

        return self;
    }

    [[nodiscard]] constexpr auto operator--(
        this Derived& self, int
    ) noexcept(std::is_nothrow_copy_constructible_v<Derived>) -> Derived
    {
        auto aux{self};
        --self;

        return aux;
    }

    constexpr auto operator==(Derived const& other) const noexcept -> bool
    {
        return node_ == other.node_;
    }

    constexpr auto operator!=(Derived const& other) const noexcept -> bool
    {
        return node_ != other.node_;
    }

private:
    explicit list_bidirectional_iterator_helper() noexcept = default;

    constexpr explicit list_bidirectional_iterator_helper(
        list_node* const node
    ) noexcept :
        node_{node}
    {
    }

    constexpr list_bidirectional_iterator_helper(
        list_bidirectional_iterator_helper const& other
    ) noexcept = default;

    constexpr list_bidirectional_iterator_helper(
        list_bidirectional_iterator_helper&& other
    ) noexcept = default;

    list_node* node_{};

    friend Derived;
};

} // namespace forfun::container::internal

#endif // FORFUN_CONTAINER_INTERNAL_LIST_ITERATOR_HELPER_HPP_
