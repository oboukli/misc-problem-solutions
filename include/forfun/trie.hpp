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
#include <string>
#include <string_view>
#include <vector>

namespace forfun::trie {

namespace experimental {

template <typename CharT = char, typename Traits = std::char_traits<CharT>>
    requires std::integral<CharT>
struct TrieNode final {
    using children_t = std::vector<std::unique_ptr<TrieNode>>;
    using value_type = CharT;
    using traits_type = Traits;

    children_t children{};
    CharT value{};
    bool is_terminal{false};

    constexpr TrieNode(CharT value_) noexcept : value{value_}
    {
    }

    constexpr TrieNode(CharT value_, bool is_terminal_) noexcept :
        value{value_}, is_terminal{is_terminal_}
    {
    }
};

template <
    typename T,
    typename StringViewT = std::basic_string_view<typename T::value_type>>
    requires std::is_same_v<T, TrieNode<typename T::value_type>>
void insert(T& root, StringViewT const& word) noexcept
{
    using len_t = StringViewT::size_type;

    auto const word_len{word.length()};
    if (word_len == len_t{0})
    {
        return;
    }

    auto const prfx{word[len_t{0}]};

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

    if (word_len == len_t{1})
    {
        parent->is_terminal = true;
    }

    insert(*parent, word.substr(len_t{1}));
}

} // namespace experimental

} // namespace forfun::trie

#endif // FORFUN_TRIE_HPP_
