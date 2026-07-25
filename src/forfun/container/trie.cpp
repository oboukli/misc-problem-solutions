// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <cassert>
#include <cstddef>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>

#include "forfun/container/trie.hpp"

namespace forfun::container::trie {

namespace {

[[nodiscard]] auto to_index(trie_node::value_type const chr) noexcept
    -> trie_node::size_type
{
    assert(chr >= trie_node::first_char);
    assert(
        chr
        < trie_node::value_type{trie_node::first_char + trie_node::num_symbols}
    );

    return static_cast<trie_node::size_type>(chr)
        - static_cast<trie_node::size_type>(trie_node::first_char);
}

[[nodiscard]] auto
search_impl(trie_node const* node_ptr, std::string_view const word) noexcept
    -> trie_node const*
{
    for (auto iter{word.cbegin()}; iter != word.cend(); ++iter)
    {
        auto const prefix{*iter};

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
        if (node_ptr->children_[to_index(prefix)] == nullptr)
        {
            return nullptr;
        }

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
        node_ptr = node_ptr->children_[to_index(prefix)].get();
    }

    return node_ptr;
}

} // namespace

auto insert(trie_node& root, std::string_view const word) -> void
{
    trie_node* node_ptr{&root};

    for (auto iter{word.cbegin()}; iter != word.cend(); ++iter)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
        auto& child{node_ptr->children_[to_index(*iter)]};

        if (child == nullptr)
        {
            child = std::make_unique<trie_node>();
        }

        node_ptr = child.get();
    }

    node_ptr->is_terminal_ = true;
}

[[nodiscard]] auto
search(trie_node const& root, std::string_view const word) noexcept -> bool
{
    trie_node const* node_ptr{search_impl(&root, word)};

    return (node_ptr != nullptr) && node_ptr->is_terminal_;
}

[[nodiscard]] auto
starts_with(trie_node const& root, std::string_view const word) noexcept -> bool
{
    return search_impl(&root, word) != nullptr;
}

/// Experimental utility to mitigate @p std::unique_ptr<trie_node> recursive
/// destructor calls.
auto clear(trie_node& root) -> void
{
    static constexpr std::size_t const initial_stack_size{128};

    std::vector<std::unique_ptr<trie_node>> reset_stack{};
    reset_stack.reserve(initial_stack_size);

    for (auto& child : root.children_)
    {
        if (child)
        {
            reset_stack.push_back(std::move(child));
        }
    }

    while (not reset_stack.empty())
    {
        auto node_uptr{std::move(reset_stack.back())};
        reset_stack.pop_back();
        for (auto& child_uptr : node_uptr->children_)
        {
            if (child_uptr)
            {
                reset_stack.push_back(std::move(child_uptr));
            }
        }
    }
}

} // namespace forfun::container::trie
