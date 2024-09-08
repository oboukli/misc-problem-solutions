// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/container/list.hpp"

#include <cassert>

#include <gsl/pointers>

#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container {

[[nodiscard]] auto list::begin() const noexcept -> iterator
{
    return iterator(head_);
}

[[nodiscard]] auto list::end() const noexcept -> iterator
{
    return iterator(end_);
}

[[nodiscard]] auto list::cbegin() const noexcept -> const_iterator
{
    return const_iterator(head_);
}

[[nodiscard]] auto list::cend() const noexcept -> const_iterator
{
    return const_iterator(end_);
}

auto list::push_back(list::value_type value) noexcept(false) -> void
{
    ++size_;
    gsl::owner<list_node*> const n{new list_node(value, tail_, end_)};

    if (head_ == end_)
    {
        head_ = n;
    }
    else
    {
        tail_->next_ = n;
    }

    tail_ = n;
    end_->previous_ = n;
}

auto list::pop_back() noexcept -> void
{
    if (tail_ == end_)
    {
        assert(head_ == end_);
        assert(size_ == size_type{});

        return;
    }

    assert(size_ > size_type{});
    assert(head_ != end_);

    if (tail_->previous_ == end_)
    {
        assert(size_ == size_type{1});
        assert(head_ == tail_);
        assert(head_->next_ == end_);
        head_ = end_;
    }
    else
    {
        assert(size_ > size_type{1});
        tail_->previous_->next_ = end_;
    }

    --size_;

    auto const* const aux{tail_};
    tail_ = tail_->previous_;
    // NOLINTNEXTLINE(cppcoreguidelines-owning-memory)
    delete aux;
}

auto list::clear() noexcept -> void
{
    assert(
        ((head_ == end_) and (size_ == size_type{}))
        or ((head_ != end_) and (size_ > size_type{}))
    );
    for (gsl::owner<list_node const*> node{head_}; node != end_;)
    {
        gsl::owner<list_node const*> const next{node->next_};

        delete node;

        node = next;
        --size_;
    }

    assert(size_ == size_type{});
    head_ = end_;
    tail_ = end_;
}

} // namespace forfun::experimental::container
