// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/linked-list-cycle/

#ifndef FORFUN_CONTAINER_FORWARD_LIST_CYCLE_HPP_
#define FORFUN_CONTAINER_FORWARD_LIST_CYCLE_HPP_

#include "forfun/container/forward_list_node.hpp"

namespace forfun::container::forward_list_cycle {

template <typename T>
[[nodiscard]] constexpr auto
has_cycle(forfun::container::forward_list_node<T> const* head) noexcept -> bool
{
    forfun::container::forward_list_node<T> const* fast{head};

    while (fast != nullptr)
    {
        fast = fast->next_ == nullptr ? nullptr : fast->next_->next_;
        if (fast == head)
        {
            return true;
        }

        head = head->next_;
    }

    return false;
}

} // namespace forfun::container::forward_list_cycle

#endif // FORFUN_CONTAINER_FORWARD_LIST_CYCLE_HPP_
