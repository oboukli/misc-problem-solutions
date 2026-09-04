// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Linked_list

#ifndef FORFUN_CONTAINER_LIST_HPP_
#define FORFUN_CONTAINER_LIST_HPP_

#include <cassert>
#include <cstddef>
#include <type_traits>

#include <gsl/pointers>

#include "forfun/common/type_traits.hpp"
#include "forfun/container/internal/list_const_iterator.hpp"
#include "forfun/container/internal/list_iterator.hpp"
#include "forfun/container/internal/list_node.hpp"

namespace forfun::container {

class list final {
public:
    using value_type = int;

    using size_type = std::size_t;

    using reference = std::add_lvalue_reference_t<value_type>;

    using const_reference
        = std::add_lvalue_reference_t<std::add_const_t<value_type>>;

    using iterator = internal::list_iterator;

    using const_iterator = internal::list_const_iterator;

    explicit list() : end_{new internal::list_node()}
    {
        head_ = end_;
        tail_ = end_;
    }

    list(list const&) = delete;

    list(list&&) = delete;

    ~list() noexcept
    {
        clear();

        delete end_;
    }

    auto operator=(list const&) -> list& = delete;

    auto operator=(list&&) noexcept -> list& = delete;

    [[nodiscard]] constexpr auto size() const noexcept -> size_type
    {
        return size_;
    }

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return size_ == size_type{};
    }

    [[nodiscard]] auto front(this auto& self) noexcept -> forfun::common::
        type_traits::reference_conditional_const_t<decltype(self), value_type>
    {
        assert(self.head_ != nullptr);

        return self.head_->value_;
    }

    [[nodiscard]] auto back(this auto& self) noexcept -> forfun::common::
        type_traits::reference_conditional_const_t<decltype(self), value_type>
    {
        assert(self.tail_ != nullptr);

        return self.tail_->value_;
    }

    auto push_back(value_type value) -> void;

    auto pop_back() noexcept -> void;

    auto clear() noexcept -> void;

    [[nodiscard]] auto begin(this auto&& self) noexcept -> forfun::common::
        type_traits::if_const_t<decltype(self), const_iterator, iterator>
    {
        using IteratorType = forfun::common::type_traits::
            if_const_t<decltype(self), const_iterator, iterator>;

        return IteratorType{self.head_};
    }

    [[nodiscard]] auto end(this auto&& self) noexcept -> forfun::common::
        type_traits::if_const_t<decltype(self), const_iterator, iterator>
    {
        using IteratorType = forfun::common::type_traits::
            if_const_t<decltype(self), const_iterator, iterator>;

        return IteratorType{self.end_};
    }

    [[nodiscard]] auto cbegin(this auto&& self) noexcept -> const_iterator
    {
        return const_iterator{self.head_};
    }

    [[nodiscard]] auto cend(this auto&& self) noexcept -> const_iterator
    {
        return const_iterator{self.end_};
    }

private:
    internal::list_node* head_;

    internal::list_node* tail_;

    gsl::owner<internal::list_node*> end_;

    size_type size_{};
};

} // namespace forfun::container

#endif // FORFUN_CONTAINER_LIST_HPP_
