// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/min-stack/

#ifndef FORFUN_CONTAINER_MIN_STACK_HPP_
#define FORFUN_CONTAINER_MIN_STACK_HPP_

#include <array>
#include <cstddef>
#include <functional>
#include <iterator>

#include "forfun/common/type_traits.hpp"

namespace forfun::container::min_stack {

namespace cache_friendly {

struct [[nodiscard]] stack_element final {
    using value_type = int;

    value_type val;

    value_type min;
};

/// Array-based fixed-capacity stack
class min_stack final {
    static constexpr std::size_t const capacity_{64};

    using internal_container_type = std::array<stack_element, capacity_>;

    internal_container_type items_{};

    internal_container_type::iterator next_iter_{std::begin(items_)};

public:
    using const_reference
        = internal_container_type::value_type::value_type const&;

    using reference = internal_container_type::value_type::value_type&;

    using size_type = internal_container_type::size_type;

    using value_type = internal_container_type::value_type::value_type;

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        using std::cbegin;

        return cbegin(items_) == next_iter_;
    }

    /// @note If the container is empty, the behavior is undefined.
    [[nodiscard]] constexpr auto min(this auto&& self) noexcept -> forfun::
        common::type_traits::forward_like_t<decltype(self), value_type>
    {
        using std::prev;

        return prev(self.next_iter_)->min;
    }

    /// @note If the container is empty, the behavior is undefined.
    constexpr auto pop() noexcept -> void
    {
        --next_iter_;
    }

    /// @note If the container is full, the behavior is undefined.
    constexpr auto push(value_type const& value) noexcept -> void
    {
        using std::begin;
        using std::min;
        using std::prev;

        next_iter_->val = value;

        if (next_iter_ == begin(items_)) [[unlikely]]
        {
            next_iter_->min = value;
        }
        else
        {
            auto const min_val{min(value, prev(next_iter_)->min)};
            next_iter_->min = min_val;
        }

        ++next_iter_;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> size_type
    {
        using std::cbegin;
        using std::distance;

        return static_cast<size_type>(distance(
            cbegin(items_), internal_container_type::const_iterator{next_iter_}
        ));
    }

    /// @note If the container is empty, the behavior is undefined.
    [[nodiscard]] auto top(this auto&& self) noexcept -> forfun::common::
        type_traits::forward_like_t<decltype(self), value_type>
    {
        using std::prev;

        return prev(self.next_iter_)->val;
    }
};

} // namespace cache_friendly

namespace double_buffered {

/// Array-based fixed-capacity stack
class min_stack final {
    static constexpr std::size_t const capacity_{64};

    using internal_container_type = std::array<int, capacity_>;

    internal_container_type items_{};

    internal_container_type mins_{};

    internal_container_type::iterator next_iter_{std::begin(items_)};

    internal_container_type::iterator min_iter_{std::begin(mins_)};

public:
    using const_reference = internal_container_type::const_reference;

    using reference = internal_container_type::reference;

    using size_type = internal_container_type::size_type;

    using value_type = internal_container_type::value_type;

    [[nodiscard]] constexpr auto empty() const noexcept -> bool
    {
        using std::cbegin;

        return cbegin(items_) == next_iter_;
    }

    /// @note If the container is empty, the behavior is undefined.
    [[nodiscard]] constexpr auto min(this auto&& self) noexcept -> forfun::
        common::type_traits::forward_like_t<decltype(self), value_type>
    {
        using std::prev;

        return *prev(self.min_iter_);
    }

    /// @note If the container is empty, the behavior is undefined.
    constexpr auto pop() noexcept -> void
    {
        --min_iter_;
        --next_iter_;
    }

    /// @note If the container is full, the behavior is undefined.
    constexpr auto push(value_type const& value) noexcept -> void
    {
        using std::begin;
        using std::less;
        using std::prev;

        *next_iter_ = value;
        ++next_iter_;

        if ((min_iter_ == begin(mins_)) || less<>{}(value, *prev(min_iter_)))
            [[unlikely]]
        {
            *min_iter_ = value;
        }
        else
        {
            *min_iter_ = *prev(min_iter_);
        }

        ++min_iter_;
    }

    [[nodiscard]] constexpr auto size() const noexcept -> size_type
    {
        using std::cbegin;
        using std::distance;

        return static_cast<size_type>(distance(
            cbegin(items_), internal_container_type::const_iterator{next_iter_}
        ));
    }

    /// @note If the container is empty, the behavior is undefined.
    [[nodiscard]] auto top(this auto&& self) noexcept -> forfun::common::
        type_traits::forward_like_t<decltype(self), value_type>
    {
        using std::prev;

        return *prev(self.next_iter_);
    }
};

} // namespace double_buffered

} // namespace forfun::container::min_stack

#endif // FORFUN_CONTAINER_MIN_STACK_HPP_
