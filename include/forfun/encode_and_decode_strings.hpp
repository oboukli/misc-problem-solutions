// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://neetcode.io/problems/string-encode-and-decode

#ifndef FORFUN_ENCODE_AND_DECODE_STRINGS_HPP_
#define FORFUN_ENCODE_AND_DECODE_STRINGS_HPP_

#include <iterator>
#include <string>
#include <string_view>
#include <vector>

namespace forfun::encode_and_decode_strings {

namespace delimited {

constexpr char const delimiter_char{' '};
constexpr char const escape_char{'~'};

namespace detail {

// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto escape(auto& os, auto const sv) -> void
{
    using SizeType = decltype(sv)::size_type;

    for (SizeType i{}; i < sv.size(); ++i)
    {
        switch (sv[i])
        {
        case delimiter_char:
            os << escape_char << delimiter_char;
            break;
        case escape_char:
            os << escape_char << escape_char;
            break;
        default:
            [[likely]] os << sv[i];
        }
    }
}

} // namespace detail

template <std::forward_iterator Iter>
auto encode(Iter iter, std::sentinel_for<Iter> auto const last, auto& os)
    -> void
{
    for (; iter != last; ++iter)
    {
        detail::escape(os, *iter);
        if (std::next(iter) != last)
        {
            os << delimiter_char;
        }
    }
}

[[nodiscard]] auto decode(std::string_view encoded) -> std::vector<std::string>;

} // namespace delimited

namespace chunked {

// Placeholder.

} // namespace chunked

} // namespace forfun::encode_and_decode_strings

#endif // FORFUN_ENCODE_AND_DECODE_STRINGS_HPP_
