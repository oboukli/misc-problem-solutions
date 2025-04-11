// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/last_stone_weight.hpp"

#include <cassert>
#include <functional>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace forfun::last_stone_weight::priority_queue_based {

[[nodiscard]] auto last_stone_weight(std::vector<int>&& stones) noexcept -> int
{
    using SizeType = std::remove_cvref_t<decltype(stones)>::size_type;
    using ValueType = std::remove_cvref_t<decltype(stones)>::value_type;

    std::priority_queue max_priority_queue(std::less<>(), std::move(stones));

    while (max_priority_queue.size() > SizeType{1})
    {
        assert(max_priority_queue.top() >= ValueType{0});

        ValueType s{max_priority_queue.top()};
        max_priority_queue.pop();

        assert(max_priority_queue.top() >= ValueType{0});

        s -= max_priority_queue.top();
        max_priority_queue.pop();
        if (s != ValueType{0})
        {
            max_priority_queue.emplace(s);
        }
    }

    return max_priority_queue.empty() ? ValueType{0} : max_priority_queue.top();
}

} // namespace forfun::last_stone_weight::priority_queue_based
