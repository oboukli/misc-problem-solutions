// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include <string_view>
#include <utility>

#include <catch2/catch_test_macros.hpp>

#include <nameof.hpp>

#include <nanobench.h>

#include "forfun/container/trie.hpp"

TEST_CASE("Trie benchmarking", "[benchmark][trie]")
{
    using std::string_view_literals::operator""sv;

    using namespace forfun::container::trie;

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

    ankerl::nanobench::Bench()

        .title("Trie")
        .relative(true)

        .run(
            NAMEOF(
                forfun::container::trie::search(
                    std::declval<trie_node&>(), std::declval<std::string_view>()
                )
            )
                .c_str(),
            [&root] noexcept -> void {
                auto const volatile r{search(root, "cathodoluminescence"sv)};
                ankerl::nanobench::doNotOptimizeAway(&r);
            }
        )

        ;
}
