// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <concepts>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

#include "forfun/container/trie.hpp"

TEST_CASE("Trie", "[trie]")
{
    SECTION("Type")
    {
        STATIC_REQUIRE(
            std::same_as<
                forfun::container::trie::trie_node::value_type,
                std::string_view::value_type>
        );
    }

    SECTION("Alphabet size")
    {
        STATIC_REQUIRE(forfun::container::trie::trie_node::num_symbols == 26UZ);
    }
}
