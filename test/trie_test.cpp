// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <memory>
#include <string_view>
#include <type_traits>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#include "forfun/trie.hpp"

TEST_CASE("Trie", "[trie]")
{
    using namespace forfun::trie::experimental;

    using std::string_view_literals::operator""sv;

    SECTION("Types")
    {
        // clang-format off
        STATIC_REQUIRE(
            std::is_same_v<TrieNode<>::children_t,
            std::vector<std::unique_ptr<TrieNode<char>>>>
        );
        STATIC_REQUIRE(std::is_same_v<TrieNode<>::value_type, char>);

        STATIC_REQUIRE(
            std::is_same_v<TrieNode<char32_t>::children_t,
            std::vector<std::unique_ptr<TrieNode<char32_t>>>>
        );
        STATIC_REQUIRE(
            std::is_same_v<TrieNode<char32_t>::value_type, char32_t>
        );
        // clang-format on
    }

    SECTION("Constructor 1")
    {
        /*constexpr*/ TrieNode const node{'B'};

        /*STATIC_*/ REQUIRE(node.value == 'B');
        /*STATIC_*/ REQUIRE_FALSE(node.is_terminal);
        /*STATIC_*/ REQUIRE(
            node.children.size() == TrieNode<>::children_t::size_type{0}
        );
    }

    SECTION("Constructor 2")
    {
        /*constexpr*/ TrieNode const node{'C', true};

        /*STATIC_*/ REQUIRE(node.value == 'C');
        /*STATIC_*/ REQUIRE(node.is_terminal);
        /*STATIC_*/ REQUIRE(
            node.children.size() == TrieNode<>::children_t::size_type{0}
        );
    }

    SECTION("Insert empty string")
    {
        TrieNode root{'X'};
        static constexpr std::string_view const word{};

        insert(root, word);

        REQUIRE(root.value == 'X');
        REQUIRE_FALSE(root.is_terminal);
        REQUIRE(root.children.size() == TrieNode<>::children_t::size_type{0});
    }

    SECTION("Insert")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word{"c"sv};

        insert(root, word);

        REQUIRE(root.value == '\0');
        REQUIRE_FALSE(root.is_terminal);
        REQUIRE(root.children.size() == TrieNode<>::children_t::size_type{1});

        REQUIRE(root.children[0]->value == 'c');
        REQUIRE(root.children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children.size()
            == TrieNode<>::children_t::size_type{0}
        );
    }

    SECTION("Insert one word")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word{"cat"sv};

        insert(root, word);

        REQUIRE(root.value == '\0');
        REQUIRE_FALSE(root.is_terminal);
        REQUIRE(root.children.size() == TrieNode<>::children_t::size_type{1});

        REQUIRE(root.children[0]->value == 'c');
        REQUIRE_FALSE(root.children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children.size()
            == TrieNode<>::children_t::size_type{1}
        );

        REQUIRE(root.children[0]->children[0]->value == 'a');
        REQUIRE_FALSE(root.children[0]->children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{1}
        );

        REQUIRE(root.children[0]->children[0]->children[0]->value == 't');
        REQUIRE(root.children[0]->children[0]->children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{0}
        );
    }

    SECTION("Insert two words")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word1{"cat"sv};
        static constexpr std::string_view const word2{"car"sv};

        insert(root, word1);
        insert(root, word2);

        REQUIRE(root.value == '\0');
        REQUIRE_FALSE(root.is_terminal);
        REQUIRE(root.children.size() == TrieNode<>::children_t::size_type{1});

        REQUIRE(root.children[0]->value == 'c');
        REQUIRE_FALSE(root.children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children.size()
            == TrieNode<>::children_t::size_type{1}
        );

        REQUIRE(root.children[0]->children[0]->value == 'a');
        REQUIRE_FALSE(root.children[0]->children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{2}
        );

        REQUIRE(root.children[0]->children[0]->children[0]->value == 't');
        REQUIRE(root.children[0]->children[0]->children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{0}
        );

        REQUIRE(root.children[0]->children[0]->children[1]->value == 'r');
        REQUIRE(root.children[0]->children[0]->children[1]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children[1]->children.size()
            == TrieNode<>::children_t::size_type{0}
        );

        SECTION("Insert prefixed")
        {
            static constexpr std::string_view const prefixed1{"catnip"sv};
            insert(root, prefixed1);

            REQUIRE(root.children[0]->value == 'c');
            REQUIRE_FALSE(root.children[0]->is_terminal);
            REQUIRE(
                root.children[0]->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(root.children[0]->children[0]->value == 'a');
            REQUIRE_FALSE(root.children[0]->children[0]->is_terminal);
            REQUIRE(
                root.children[0]->children[0]->children.size()
                == TrieNode<>::children_t::size_type{2}
            );

            REQUIRE(root.children[0]->children[0]->children[0]->value == 't');
            REQUIRE(root.children[0]->children[0]->children[0]->is_terminal);
            REQUIRE(
                root.children[0]->children[0]->children[0]->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(
                root.children[0]->children[0]->children[0]->children[0]->value
                == 'n'
            );
            REQUIRE_FALSE(
                // clang-format off
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->is_terminal
                // clang-format on
            );
            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->value
                == 'i'
            );
            REQUIRE_FALSE(
                // clang-format off
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->is_terminal
                // clang-format on
            );
            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->value
                == 'p'
            );
            REQUIRE(root.children[0]
                        ->children[0]
                        ->children[0]
                        ->children[0]
                        ->children[0]
                        ->children[0]
                        ->is_terminal);
            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children.size()
                == TrieNode<>::children_t::size_type{0}
            );

            REQUIRE(root.children[0]->children[0]->children[1]->value == 'r');
            REQUIRE(root.children[0]->children[0]->children[1]->is_terminal);
            REQUIRE(
                root.children[0]->children[0]->children[1]->children.size()
                == TrieNode<>::children_t::size_type{0}
            );
        }
    }

    SECTION("Insert two independent words")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word1{"cat"sv};
        static constexpr std::string_view const word2{"dog"sv};

        insert(root, word1);
        insert(root, word2);

        REQUIRE(root.value == '\0');
        REQUIRE_FALSE(root.is_terminal);
        REQUIRE(root.children.size() == TrieNode<>::children_t::size_type{2});

        REQUIRE(root.children[0]->value == 'c');
        REQUIRE_FALSE(root.children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children.size()
            == TrieNode<>::children_t::size_type{1}
        );

        REQUIRE(root.children[0]->children[0]->value == 'a');
        REQUIRE_FALSE(root.children[0]->children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{1}
        );

        REQUIRE(root.children[0]->children[0]->children[0]->value == 't');
        REQUIRE(root.children[0]->children[0]->children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{0}
        );

        REQUIRE(root.children[1]->value == 'd');
        REQUIRE_FALSE(root.children[1]->is_terminal);
        REQUIRE(
            root.children[1]->children.size()
            == TrieNode<>::children_t::size_type{1}
        );

        REQUIRE(root.children[1]->children[0]->value == 'o');
        REQUIRE_FALSE(root.children[1]->children[0]->is_terminal);
        REQUIRE(
            root.children[1]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{1}
        );

        REQUIRE(root.children[1]->children[0]->children[0]->value == 'g');
        REQUIRE(root.children[1]->children[0]->children[0]->is_terminal);
        REQUIRE(
            root.children[1]->children[0]->children[0]->children.size()
            == TrieNode<>::children_t::size_type{0}
        );

        SECTION("Insert prefixed")
        {
            static constexpr std::string_view const prefixed1{"catnip"sv};
            insert(root, prefixed1);

            REQUIRE(root.children[0]->value == 'c');
            REQUIRE_FALSE(root.children[0]->is_terminal);
            REQUIRE(
                root.children[0]->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(root.children[0]->children[0]->value == 'a');
            REQUIRE_FALSE(root.children[0]->children[0]->is_terminal);
            REQUIRE(
                root.children[0]->children[0]->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(root.children[0]->children[0]->children[0]->value == 't');
            REQUIRE(root.children[0]->children[0]->children[0]->is_terminal);
            REQUIRE(
                root.children[0]->children[0]->children[0]->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(
                root.children[0]->children[0]->children[0]->children[0]->value
                == 'n'
            );
            REQUIRE_FALSE(
                // clang-format off
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->is_terminal
                // clang-format off
            );
            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->value
                == 'i'
            );
            REQUIRE_FALSE(
                // clang-format off
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->is_terminal
                // clang-format on
            );
            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->value
                == 'p'
            );
            REQUIRE(root.children[0]
                        ->children[0]
                        ->children[0]
                        ->children[0]
                        ->children[0]
                        ->children[0]
                        ->is_terminal);
            REQUIRE(
                root.children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children[0]
                    ->children.size()
                == TrieNode<>::children_t::size_type{0}
            );

            REQUIRE(root.children[1]->value == 'd');
            REQUIRE_FALSE(root.children[1]->is_terminal);
            REQUIRE(
                root.children[1]->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(root.children[1]->children[0]->value == 'o');
            REQUIRE_FALSE(root.children[1]->children[0]->is_terminal);
            REQUIRE(
                root.children[1]->children[0]->children.size()
                == TrieNode<>::children_t::size_type{1}
            );

            REQUIRE(root.children[1]->children[0]->children[0]->value == 'g');
            REQUIRE(root.children[1]->children[0]->children[0]->is_terminal);
            REQUIRE(
                root.children[1]->children[0]->children[0]->children.size()
                == TrieNode<>::children_t::size_type{0}
            );
        }
    }
}
