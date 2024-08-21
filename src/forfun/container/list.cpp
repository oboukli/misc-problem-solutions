// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/container/list.hpp"

#include <cassert>

#include "forfun/container/internal/list_node.hpp"

namespace forfun::experimental::container {

auto list::push_back(list::value_type value) noexcept -> void
{
    ++size_;
    list_node* const n{new list_node(value, tail_, nullptr)};

    if (head_ == nullptr)
    {
        head_ = n;
    }
    else
    {
        tail_->next_ = n;
    }

    tail_ = n;
}

auto list::pop_back() noexcept -> void
{
    if (tail_ == nullptr)
    {
        assert(head_ == nullptr);
        assert(size_ == size_type{});

        return;
    }

    assert(size_ > size_type{});
    assert(head_ != nullptr);

    if (tail_->previous_ == nullptr)
    {
        assert(size_ == size_type{1});
        assert(head_ == tail_);
        assert(head_->next_ == nullptr);
        head_ = nullptr;
    }
    else
    {
        assert(size_ > size_type{1});
        tail_->previous_->next_ = nullptr;
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
        ((head_ == nullptr) and (size_ == size_type{}))
        or ((head_ != nullptr) and (size_ > size_type{}))
    );
    for (list_node const* node{head_}; node != nullptr;)
    {
        list_node const* const next{node->next_};
        delete node;

        node = next;
        --size_;
    }

    assert(size_ == size_type{});
    head_ = nullptr;
    tail_ = nullptr;
}

} // namespace forfun::experimental::container
