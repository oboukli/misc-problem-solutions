// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/encode_and_decode_strings.hpp"

#include <ios>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace forfun::encode_and_decode_strings {

namespace delimited {

namespace {

auto unescape(auto& ss, auto const sv) -> bool
{
    using SizeType = decltype(sv)::size_type;

    bool pop_next{false};
    std::streamsize chunk_start{0};
    SizeType i{0};
    for (; i < sv.size(); ++i)
    {
        if ((sv[i] == escape_char) || (sv[i] == delimiter_char))
        {
            if (pop_next)
            {
                ss << sv[i];
            }
            else
            {
                ss.write(
                    sv.data() + chunk_start,
                    static_cast<std::streamsize>(i) - chunk_start
                );

                if (sv[i] == delimiter_char)
                {
                    return true;
                }

                chunk_start = static_cast<std::streamsize>(i + 2);
            }
            pop_next = !pop_next;
        }
    }

    ss.write(
        sv.data() + chunk_start, static_cast<std::streamsize>(i) - chunk_start
    );

    return false;
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
    bool has_delimiter{true};
    // clang-format off
    for (SizeType p{0};
        ((p = encoded.find(delimiter_char, p)) != std::string_view::npos);)
    // clang-format on
    {
        auto const esc{
            encoded.substr(sub_start, p - sub_start).find(escape_char)
        };

        if (has_delimiter && (esc == std::string_view::npos))
        {
            decoded_tokens.emplace_back(
                encoded.data() + sub_start, p - sub_start
            );
            sub_start = ++p;

            continue;
        }

        if (esc != std::string_view::npos)
        {
            ss.write(
                encoded.data() + sub_start, static_cast<std::streamsize>(esc)
            );
            sub_start += esc;
        }

        has_delimiter
            = unescape(ss, encoded.substr(sub_start, (p + 1) - sub_start));

        if (has_delimiter)
        {
            decoded_tokens.emplace_back(
                ss.view().substr(0, static_cast<SizeType>(ss.tellp()))
            );
            ss.seekp(0);
        }

        sub_start = ++p;
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
