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

    SECTION("Types")
    {
        STATIC_REQUIRE(
            std::is_same_v<
                TrieNode<>::children_t,
                std::vector<std::unique_ptr<TrieNode<>>>>
        );
        STATIC_REQUIRE(std::is_same_v<TrieNode<>::value_type, char>);

        STATIC_REQUIRE(
            std::is_same_v<
                TrieNode<char32_t>::children_t,
                std::vector<std::unique_ptr<TrieNode<char32_t>>>>
        );
        STATIC_REQUIRE(
            std::is_same_v<TrieNode<char32_t>::value_type, char32_t>
        );
    }

    SECTION("Constructor 1")
    {
        /*constexpr*/ TrieNode const node{'B'};

        /*STATIC_*/ REQUIRE(node.value == 'B');
        /*STATIC_*/ REQUIRE_FALSE(node.is_terminal);
        /*STATIC_*/ REQUIRE(
            node.children.size() == TrieNode<>::children_t::size_type{}
        );
    }

    SECTION("Constructor 2")
    {
        /*constexpr*/ TrieNode const node{'C', true};

        /*STATIC_*/ REQUIRE(node.value == 'C');
        /*STATIC_*/ REQUIRE(node.is_terminal);
        /*STATIC_*/ REQUIRE(
            node.children.size() == TrieNode<>::children_t::size_type{}
        );
    }

    SECTION("Insert empty string")
    {
        TrieNode root{'X'};
        static constexpr std::string_view const word{};

        insert(root, word);

        REQUIRE(root.value == 'X');
        REQUIRE_FALSE(root.is_terminal);
        REQUIRE(root.children.size() == TrieNode<>::children_t::size_type{});
    }

    SECTION("Insert")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word{"c"};

        insert(root, word);

        REQUIRE(root.value == '\0');
        REQUIRE_FALSE(root.is_terminal);
        REQUIRE(root.children.size() == TrieNode<>::children_t::size_type{1});

        REQUIRE(root.children[0]->value == 'c');
        REQUIRE(root.children[0]->is_terminal);
        REQUIRE(
            root.children[0]->children.size()
            == TrieNode<>::children_t::size_type{}
        );
    }

    SECTION("Insert one word")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word{"cat"};

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
            == TrieNode<>::children_t::size_type{}
        );
    }

    SECTION("Insert two words")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word1{"cat"};
        static constexpr std::string_view const word2{"car"};

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
            == TrieNode<>::children_t::size_type{}
        );

        REQUIRE(root.children[0]->children[0]->children[1]->value == 'r');
        REQUIRE(root.children[0]->children[0]->children[1]->is_terminal);
        REQUIRE(
            root.children[0]->children[0]->children[1]->children.size()
            == TrieNode<>::children_t::size_type{}
        );

        SECTION("Insert prefixed")
        {
            static constexpr std::string_view const prefixed1{"catnip"};
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
                == TrieNode<>::children_t::size_type{}
            );

            REQUIRE(root.children[0]->children[0]->children[1]->value == 'r');
            REQUIRE(root.children[0]->children[0]->children[1]->is_terminal);
            REQUIRE(
                root.children[0]->children[0]->children[1]->children.size()
                == TrieNode<>::children_t::size_type{}
            );
        }
    }

    SECTION("Insert two independent words")
    {
        TrieNode root{'\0'};
        static constexpr std::string_view const word1{"cat"};
        static constexpr std::string_view const word2{"dog"};

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
            == TrieNode<>::children_t::size_type{}
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
            == TrieNode<>::children_t::size_type{}
        );

        SECTION("Insert prefixed")
        {
            static constexpr std::string_view const prefixed1{"catnip"};
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
                == TrieNode<>::children_t::size_type{}
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
                == TrieNode<>::children_t::size_type{}
            );
        }
    }
}
