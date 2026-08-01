// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Trie

#ifndef FORFUN_CONTAINER_TRIE_HPP_
#define FORFUN_CONTAINER_TRIE_HPP_

#include <array>
#include <cassert>
#include <cstddef>
#include <memory>
#include <string_view>

namespace forfun::container::trie {

struct trie_node final {
    static constexpr std::size_t const num_symbols{26};

    using value_type = std::string_view::value_type;

    using children_t = std::array<std::unique_ptr<trie_node>, num_symbols>;

    using size_type = children_t::size_type;

    static constexpr value_type const first_char{'a'};

    static_assert(
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        (value_type{'a' + 13} == 'n') and (value_type{'a' + 25} == 'z')
    );

    // NOLINTBEGIN(misc-non-private-member-variables-in-classes)
    children_t children_{};

    bool is_terminal_{false};
    // NOLINTEND(misc-non-private-member-variables-in-classes)
};

auto insert(trie_node& root, std::string_view word) -> void;

[[nodiscard]] auto search(trie_node const& root, std::string_view word) noexcept
    -> bool;

[[nodiscard]] auto
starts_with(trie_node const& root, std::string_view word) noexcept -> bool;

auto clear(trie_node& root) noexcept -> void;

} // namespace forfun::container::trie

#endif // FORFUN_CONTAINER_TRIE_HPP_
