// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/encode_and_decode_strings.hpp"

#include <ios>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace forfun::encode_and_decode_strings {

namespace delimited {

namespace {

auto unescape(auto& ss, auto const sv) -> void
{
    using SizeType = decltype(sv)::size_type;

    if (sv.size() < SizeType{2}) [[unlikely]]
    {
        ss.write(sv.data(), static_cast<std::streamsize>(sv.size()));

        return;
    }

    std::streamsize chunk_start{0};
    SizeType i{0};
    for (; i < sv.size(); ++i)
    {
        if (sv[i] == escape_char)
        {
            if ((i + SizeType{1}) < sv.size() && sv[i + 1] == escape_char)
            {
                ++i;
            }
            ss.write(
                sv.data() + chunk_start,
                static_cast<std::streamsize>(i) - chunk_start
            );

            chunk_start = static_cast<std::streamsize>(i + 1);

            continue;
        }
    }

    ss.write(
        sv.data() + chunk_start, static_cast<std::streamsize>(i) - chunk_start
    );
}

} // namespace

[[nodiscard]] auto decode(std::string_view const encoded)
    -> std::vector<std::string>
{
    using SizeType = decltype(encoded)::size_type;

    if (encoded.empty()) [[unlikely]]
    {
        return {};
    }

    std::vector<std::string> decoded_tokens{};

    std::ostringstream ss{};
    SizeType sub_start{0};
    // clang-format off
    for (SizeType p{0}; p < encoded.size()
         && ((p = encoded.find(delimiter_char, p)) != std::string_view::npos);)
    // clang-format on
    {
        if ((p != SizeType{0}) && (encoded[p - 1] == escape_char))
        {
            ++p;
            continue;
        }

        unescape(ss, encoded.substr(sub_start, p - sub_start));
        decoded_tokens.emplace_back(
            ss.view().substr(0, static_cast<SizeType>(ss.tellp()))
        );

        sub_start = ++p;
        ss.seekp(0);
    }
    unescape(ss, encoded.substr(sub_start, encoded.size() - sub_start));
    decoded_tokens.emplace_back(
        ss.view().substr(0, static_cast<SizeType>(ss.tellp()))
    );

    return decoded_tokens;
}

} // namespace delimited

namespace chunked {

// Placeholder.

} // namespace chunked

} // namespace forfun::encode_and_decode_strings
