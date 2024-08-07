// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://en.wikipedia.org/wiki/Trie

#ifndef FORFUN_TRIE_HPP_
#define FORFUN_TRIE_HPP_

#include <concepts>
#include <memory>
#include <string_view>
#include <vector>

namespace forfun::trie::experimental {

template <std::integral CharT = char>
struct TrieNode final {
    using children_t = std::vector<std::unique_ptr<TrieNode>>;
    using value_type = CharT;

    explicit constexpr TrieNode(CharT const value_) noexcept : value{value_}
    {
    }

    explicit constexpr TrieNode(
        CharT const value_, bool const is_terminal_
    ) noexcept :
        value{value_}, is_terminal{is_terminal_}
    {
    }

    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    children_t children{};
    CharT value{};
    bool is_terminal{false};
    // NOLINTEND(misc-non-private-member-variables-in-classes)
};

template <typename T>
using StringViewT = std::basic_string_view<typename T::value_type>;

template <typename T>
    requires std::same_as<T, TrieNode<typename T::value_type>>
auto insert(T& root, StringViewT<T> const& word) noexcept -> void
{
    using LenT = StringViewT<T>::size_type;

    auto const word_len{word.length()};
    if (word_len == LenT{0})
    {
        return;
    }

    auto const prfx{word[LenT{0}]};

    T* parent{nullptr};
    for (auto const& node_ptr : root.children)
    {
        if (node_ptr->value == prfx)
        {
            parent = node_ptr.get();
            break;
        }
    }

    if (parent == nullptr)
    {
        root.children.push_back(std::make_unique<T>(prfx));
        parent = root.children.crbegin()->get();
    }

    if (word_len == LenT{1})
    {
        parent->is_terminal = true;
    }

    insert(*parent, word.substr(LenT{1}));
}

} // namespace forfun::trie::experimental

#endif // FORFUN_TRIE_HPP_
