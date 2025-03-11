// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://neetcode.io/problems/string-encode-and-decode

#ifndef FORFUN_ENCODE_AND_DECODE_STRINGS_HPP_
#define FORFUN_ENCODE_AND_DECODE_STRINGS_HPP_

#include <concepts>
#include <ios>
#include <iterator>
#include <ostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace forfun::encode_and_decode_strings {

namespace delimited {

constexpr char const delimiter_char{' '};
constexpr char const escape_char{'~'};

namespace detail {

template <
    typename OStream,
    typename Sv,
    typename CharT = char,
    typename Traits = std::char_traits<CharT>>
    requires std::derived_from<OStream, std::basic_ostream<CharT, Traits>>
    and std::convertible_to<Sv, std::basic_string_view<CharT, Traits>>
// NOLINTNEXTLINE(performance-unnecessary-value-param)
auto escape(OStream& os, Sv const sv) -> void
{
    using SizeType = std::basic_string_view<CharT, Traits>::size_type;

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

template <typename OS, typename CharT, typename Traits>
    requires std::derived_from<OS, std::basic_ostream<CharT, Traits>>
auto unescape(OS& os, std::basic_string_view<CharT, Traits> const sv) -> bool
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
                os << sv[i];
            }
            else
            {
                os.write(
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

    os.write(
        sv.data() + chunk_start, static_cast<std::streamsize>(i) - chunk_start
    );

    return false;
}

} // namespace detail

template <
    std::forward_iterator Iter,
    std::sentinel_for<Iter> Sentinel,
    typename OS,
    typename CharT = std::iter_value_t<Iter>::value_type,
    typename Traits = std::char_traits<CharT>>
// clang-format off
    requires std::derived_from<OS, std::basic_ostream<CharT, Traits>>
        and std::convertible_to<
            std::iter_value_t<Iter>,
            std::basic_string_view<CharT, Traits>>
// clang-format on
auto encode(Iter iter, Sentinel const last, OS& os) -> void
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

template <typename CharT, typename Traits>
[[nodiscard]] auto decode(std::basic_string_view<CharT, Traits> const encoded)
    -> std::vector<std::string>
{
    using SizeType = decltype(encoded)::size_type;

    if (encoded.empty()) [[unlikely]]
    {
        return {};
    }

    std::vector<std::string> decoded_tokens{};

    std::ostringstream os{};
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
            os.write(
                encoded.data() + sub_start, static_cast<std::streamsize>(esc)
            );
            sub_start += esc;
        }

        has_delimiter = detail::unescape(
            os, encoded.substr(sub_start, (p + 1) - sub_start)
        );

        if (has_delimiter)
        {
            decoded_tokens.emplace_back(
                os.view().substr(0, static_cast<SizeType>(os.tellp()))
            );
            os.seekp(0);
        }

        sub_start = ++p;
    }
    detail::unescape(os, encoded.substr(sub_start, encoded.size() - sub_start));
    decoded_tokens.emplace_back(
        os.view().substr(0, static_cast<SizeType>(os.tellp()))
    );

    return decoded_tokens;
}

} // namespace delimited

namespace chunked {

// Placeholder.

} // namespace chunked

} // namespace forfun::encode_and_decode_strings

#endif // FORFUN_ENCODE_AND_DECODE_STRINGS_HPP_
