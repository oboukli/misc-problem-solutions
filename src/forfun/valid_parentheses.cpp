// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/valid_parentheses.hpp"

#include <cassert>
#include <deque>
#include <memory>
#include <string_view>
#include <vector>

namespace forfun::valid_parentheses {

namespace {

[[nodiscard]] auto inline map_open_to_closed(char8_t c) noexcept -> char8_t
{
    switch (c)
    {
    case u8'(':
        return u8')';
    case u8'[':
        return u8']';
    default:
        return u8'}';
    }
}

} // namespace

namespace ascii_optimized {

[[nodiscard]] auto is_valid(std::u8string_view const s) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::vector<char8_t> expected;
    expected.reserve(s.size());

    ConstIter const cend{s.cend()};
    for (ConstIter itr{s.cbegin()}; itr != cend; ++itr)
    {
        if (char8_t const c{*itr};
            (c & char8_t{0b00000011}) == char8_t{0b00000001})
        {
            if (expected.empty() || (expected.back() != c))
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(c == u8'(' ? u8')' : c + char8_t{2});
        }
    }

    return expected.empty();
}

} // namespace ascii_optimized

namespace circuit_breaker {

[[nodiscard]] auto is_valid(std::u8string_view const s) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;
    using SizeType = std::u8string_view::size_type;

    // Odd strings are always invalid.
    if ((s.size() % SizeType{2}) != SizeType{0})
    {
        return false;
    }

    std::vector<char8_t> expected{};
    expected.reserve(s.size());

    ConstIter const cend{s.cend()};
    for (ConstIter itr{s.cbegin()}; itr != cend; ++itr)
    {
        if (char8_t const c{*itr}; (c == u8')') || (c == u8']') || (c == u8'}'))
        {
            if (expected.empty() || expected.back() != c)
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(map_open_to_closed(c));
        }
    }

    return expected.empty();
}

} // namespace circuit_breaker

namespace deque_based {

[[nodiscard]] auto is_valid(std::u8string_view const s) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::deque<char8_t> expected{};

    ConstIter const cend{s.cend()};
    for (ConstIter itr{s.cbegin()}; itr != cend; ++itr)
    {
        if (char8_t const c{*itr}; (c == u8')') || (c == u8']') || (c == u8'}'))
        {
            if (expected.empty() || expected.back() != c)
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(map_open_to_closed(c));
        }
    }

    return expected.empty();
}

} // namespace deque_based

namespace dyn_array_based {

/// @note Utilizes odd string circuit breaker and a dynamic array.
[[nodiscard]] auto is_valid(std::u8string_view const s) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;
    using SizeType = std::u8string_view::size_type;

    // Odd strings are always invalid.
    if ((s.size() % SizeType{2}) != SizeType{0})
    {
        return false;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
    std::unique_ptr<char8_t[]> const expected
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
        = std::make_unique_for_overwrite<char8_t[]>(s.size());

    char8_t* const expected_begin{expected.get()};
    assert(expected_begin != nullptr);

    char8_t* back_ptr{nullptr};
    char8_t back{};

    ConstIter const cend{s.cend()};
    for (ConstIter itr{s.cbegin()}; itr != cend; ++itr)
    {
        if (char8_t const c{*itr}; (c == u8')') || (c == u8']') || (c == u8'}'))
        {
            if ((back_ptr == nullptr) || (back != c))
            {
                return false;
            }

            if (back_ptr == expected_begin)
            {
                back_ptr = nullptr;
                back = char8_t{};
            }
            else
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                --back_ptr;
                back = *back_ptr;
            }
        }
        else
        {
            back = map_open_to_closed(c);
            if (back_ptr == nullptr)
            {
                back_ptr = expected_begin;
            }
            else
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                ++back_ptr;
            }

            assert(back_ptr != nullptr);
            *back_ptr = back;
        }
    }

    return back_ptr == nullptr;
}

} // namespace dyn_array_based

namespace vector_based {

[[nodiscard]] auto is_valid(std::u8string_view const s) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::vector<char8_t> expected{};
    expected.reserve(s.size());

    ConstIter const cend{s.cend()};
    for (ConstIter itr{s.cbegin()}; itr != cend; ++itr)
    {
        if (char8_t const c{*itr}; (c == u8')') || (c == u8']') || (c == u8'}'))
        {
            if (expected.empty() || expected.back() != c)
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(map_open_to_closed(c));
        }
    }

    return expected.empty();
}

} // namespace vector_based

namespace vector_based_demi_allocated {

[[nodiscard]] auto is_valid(std::u8string_view const s) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::vector<char8_t> expected{};
    expected.reserve(s.size() / 2U);

    char8_t back{};
    ConstIter const cend{s.cend()};
    for (ConstIter itr{s.cbegin()}; itr != cend; ++itr)
    {
        if (char8_t const c{*itr}; (c == u8')') || (c == u8']') || (c == u8'}'))
        {
            if (expected.empty() || back != c)
            {
                return false;
            }

            expected.pop_back();

            back = expected.empty() ? char8_t{} : expected.back();
        }
        else
        {
            back = map_open_to_closed(c);
            expected.push_back(back);
        }
    }

    return expected.empty();
}

} // namespace vector_based_demi_allocated

} // namespace forfun::valid_parentheses
