// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <algorithm>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/trie.hpp"

TEST_CASE("Trie", "[trie]")
{
    using forfun::container::trie::insert;
    using forfun::container::trie::search;
    using forfun::container::trie::starts_with;
    using forfun::container::trie::trie_node;

    using std::string_view_literals::operator""sv;

    SECTION("Node constructor (case 1)")
    {
        trie_node const node;

        REQUIRE_FALSE(node.is_terminal_);
    }

    SECTION("Node constructor (case 2)")
    {
        trie_node const node{};

        REQUIRE_FALSE(node.is_terminal_);
    }

    SECTION("Empty string")
    {
        static constexpr std::string_view const word{};

        trie_node root{};

        insert(root, word);

        REQUIRE(root.is_terminal_);

        REQUIRE(starts_with(root, ""sv));

        REQUIRE(search(root, ""sv));
    }

    SECTION("One letter")
    {
        static constexpr std::string_view const word{"c"};

        trie_node root{};

        insert(root, word);

        REQUIRE(root.children_['c' - trie_node::first_char] != nullptr);

        REQUIRE_FALSE(root.is_terminal_);

        REQUIRE(root.children_['c' - trie_node::first_char]->is_terminal_);

        REQUIRE(starts_with(root, "c"sv));

        REQUIRE(search(root, "c"sv));
    }

    SECTION("Two-letter word")
    {
        static constexpr std::string_view const word{"go"};

        trie_node root{};

        insert(root, word);

        REQUIRE_FALSE(root.is_terminal_);

        REQUIRE(starts_with(root, "g"sv));

        REQUIRE(starts_with(root, "go"sv));

        REQUIRE(search(root, "go"sv));
    }

    SECTION("Three-letter word")
    {
        static constexpr std::string_view const word{"cat"};

        trie_node root{};

        insert(root, word);

        REQUIRE_FALSE(root.is_terminal_);

        REQUIRE(starts_with(root, "c"sv));

        REQUIRE(starts_with(root, "ca"sv));

        REQUIRE(starts_with(root, "cat"sv));

        REQUIRE(search(root, "cat"sv));
    }

    SECTION("Four-letter word")
    {
        static constexpr std::string_view const word{"bear"};

        trie_node root{};

        insert(root, word);

        REQUIRE_FALSE(root.is_terminal_);

        REQUIRE(starts_with(root, "b"sv));

        REQUIRE(starts_with(root, "be"sv));

        REQUIRE(starts_with(root, "bea"sv));

        REQUIRE(starts_with(root, "bear"sv));

        REQUIRE(search(root, "bear"sv));
    }

    SECTION("Twenty-six-letter word")
    {
        static constexpr std::string_view const word{
            "abcdefghijklmnopqrstuvwxyz"
        };

        trie_node root{};

        insert(root, word);

        REQUIRE(starts_with(root, "abc"sv));

        REQUIRE(search(root, "abcdefghijklmnopqrstuvwxyz"sv));
    }

    SECTION("Two words")
    {
        static constexpr std::string_view const word1{"cat"};
        static constexpr std::string_view const word2{"car"};

        trie_node root{};

        insert(root, word1);
        insert(root, word2);

        REQUIRE_FALSE(root.is_terminal_);

        REQUIRE(starts_with(root, "c"sv));

        REQUIRE(starts_with(root, "ca"sv));

        REQUIRE(starts_with(root, "cat"sv));

        REQUIRE(starts_with(root, "car"sv));

        REQUIRE(search(root, "cat"sv));

        REQUIRE(search(root, "car"sv));
    }

    SECTION("Three words")
    {
        static constexpr std::string_view const word1{"cat"};
        static constexpr std::string_view const word2{"car"};
        static constexpr std::string_view const word3{"dog"};

        trie_node root{};

        insert(root, word1);
        insert(root, word2);
        insert(root, word3);

        REQUIRE_FALSE(root.is_terminal_);

        REQUIRE(starts_with(root, "c"sv));

        REQUIRE(starts_with(root, "ca"sv));

        REQUIRE(starts_with(root, "cat"sv));

        REQUIRE(starts_with(root, "car"sv));

        REQUIRE(starts_with(root, "d"sv));

        REQUIRE(starts_with(root, "do"sv));

        REQUIRE(starts_with(root, "dog"sv));

        REQUIRE(search(root, "cat"sv));

        REQUIRE(search(root, "car"sv));

        REQUIRE(search(root, "dog"sv));
    }

    SECTION("Eight words (benchmark case)")
    {
        static constexpr std::string_view const word1{"category"};
        static constexpr std::string_view const word2{"car"};
        static constexpr std::string_view const word3{"cat"};
        static constexpr std::string_view const word4{"dog"};
        static constexpr std::string_view const word5{"catnip"};
        static constexpr std::string_view const word6{"dogma"};
        static constexpr std::string_view const word7{"catalyst"};
        static constexpr std::string_view const word8{"cathodoluminescence"};

        trie_node root{};

        insert(root, word1);
        insert(root, word2);
        insert(root, word3);
        insert(root, word4);
        insert(root, word5);
        insert(root, word6);
        insert(root, word7);
        insert(root, word8);

        REQUIRE(search(root, "cathodoluminescence"sv));

        REQUIRE(starts_with(root, "cathodoluminescence"sv));
    }

    SECTION("Idempotency")
    {
        static constexpr std::string_view const word{"idempotent"};

        trie_node root{};

        insert(root, word);
        insert(root, word);

        REQUIRE(starts_with(root, "id"sv));

        REQUIRE(search(root, "idempotent"sv));
    }

    SECTION("Word is contained in, but does not prefix, words in trie")
    {
        static constexpr std::string_view const word1{"algorithm"};
        static constexpr std::string_view const word2{"mango"};

        trie_node root{};

        insert(root, word1);
        insert(root, word2);

        REQUIRE_FALSE(starts_with(root, "go"sv));

        REQUIRE_FALSE(search(root, "go"sv));

        REQUIRE(search(root, "mango"sv));

        REQUIRE(search(root, "algorithm"sv));
    }

    SECTION("Clear empty trie")
    {
        trie_node root{};

        forfun::container::trie::clear(root);

        REQUIRE(
            std::ranges::all_of(
                root.children_, [](auto const& uptr) noexcept -> bool {
                    return not static_cast<bool>(uptr);
                }
            )
        );
    }

    SECTION("Clear non-empty trie")
    {
        static constexpr std::string_view const word1{"category"};
        static constexpr std::string_view const word2{"car"};
        static constexpr std::string_view const word3{"cat"};
        static constexpr std::string_view const word4{"dog"};
        static constexpr std::string_view const word5{"catnip"};
        static constexpr std::string_view const word6{"dogma"};
        static constexpr std::string_view const word7{"catalyst"};
        static constexpr std::string_view const word8{"cathodoluminescence"};

        trie_node root{};

        insert(root, word1);
        insert(root, word2);
        insert(root, word3);
        insert(root, word4);
        insert(root, word5);
        insert(root, word6);
        insert(root, word7);
        insert(root, word8);

        forfun::container::trie::clear(root);

        REQUIRE(
            std::ranges::all_of(
                root.children_, [](auto const& uptr) noexcept -> bool {
                    return not static_cast<bool>(uptr);
                }
            )
        );
    }
}
