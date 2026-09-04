// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Linked_list

#ifndef FORFUN_CONTAINER_FORWARD_LIST_HPP_
#define FORFUN_CONTAINER_FORWARD_LIST_HPP_

#include <cassert>
#include <concepts>
#include <type_traits>
#include <utility>

#include <gsl/pointers>

#include "forfun/common/type_traits.hpp"
#include "forfun/container/forward_list_node.hpp"

namespace forfun::container {

template <typename T>
    requires std::integral<T>
class forward_list final {
public:
    using value_type = T;

    using reference = std::add_lvalue_reference_t<value_type>;

    using const_reference
        = std::add_lvalue_reference_t<std::add_const_t<value_type>>;

    constexpr forward_list() noexcept = default;

    forward_list(forward_list const&) = delete;

    forward_list(forward_list&&) = delete;

    constexpr ~forward_list() noexcept
    {
        clear();
    }

    auto operator=(forward_list const&) -> forward_list& = delete;

    auto operator=(forward_list&&) -> forward_list& = delete;

    [[nodiscard]] constexpr auto front(this auto& self) noexcept
        -> forfun::common::type_traits::
            reference_conditional_const_t<decltype(self), value_type>
    {
        assert(self.head_ != nullptr);

        return self.head_->value_;
    }

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        return head_ == nullptr;
    }

    auto push_front(T&& value) -> void
    {
        auto* node_ptr{
            new forfun::container::forward_list_node<T>(std::move(value))
        };

        node_ptr->next_ = std::exchange(head_, node_ptr);
    }

    /// @note The behavior is undefined when popping the front of an empty
    /// container.
    auto pop_front() noexcept -> void
    {
        assert(head_ != nullptr);

        delete std::exchange(head_, head_->next_);
    }

    constexpr auto clear() noexcept -> void
    {
        while (head_ != nullptr)
        {
            forfun::container::forward_list_node<T>* const next{head_->next_};

            delete head_;

            // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
            head_ = next;
        }
    }

    constexpr auto reverse() noexcept -> void
    {
        forfun::container::forward_list_node<T>* prev{nullptr};

        while (head_ != nullptr)
        {
            forfun::container::forward_list_node<T>* next{head_->next_};

            head_->next_ = prev;

            prev = head_;
            // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
            head_ = next;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
        head_ = prev;
    }

private:
    gsl::owner<forfun::container::forward_list_node<T>*> head_{};
};

} // namespace forfun::container

#endif // FORFUN_CONTAINER_FORWARD_LIST_HPP_
