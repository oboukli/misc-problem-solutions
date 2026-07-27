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

[[nodiscard]] auto map_open_to_closed(char8_t const chr) noexcept -> char8_t
{
    switch (chr)
    {
    case u8'(':
        return u8')';
    case u8'[':
        return u8']';
    default:
        break;
    }

    return u8'}';
}

} // namespace

namespace ascii_optimized {

[[nodiscard]] auto is_valid(std::u8string_view const view) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::vector<char8_t> expected;
    expected.reserve(view.size());

    for (ConstIter iter{view.cbegin()}; iter != view.cend(); ++iter)
    {
        if (char8_t const chr{*iter};
            (chr & char8_t{0b00000011}) == char8_t{0b00000001})
        {
            if (expected.empty() || (expected.back() != chr))
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(chr == u8'(' ? u8')' : chr + char8_t{2});
        }
    }

    return expected.empty();
}

} // namespace ascii_optimized

namespace circuit_breaker {

[[nodiscard]] auto is_valid(std::u8string_view const view) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;
    using SizeType = std::u8string_view::size_type;

    // Odd strings are always invalid.
    if ((view.size() % SizeType{2}) != SizeType{})
    {
        return false;
    }

    std::vector<char8_t> expected{};
    expected.reserve(view.size());

    for (ConstIter iter{view.cbegin()}; iter != view.cend(); ++iter)
    {
        if (char8_t const chr{*iter};
            (chr == u8')') || (chr == u8']') || (chr == u8'}'))
        {
            if (expected.empty() || expected.back() != chr)
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(map_open_to_closed(chr));
        }
    }

    return expected.empty();
}

} // namespace circuit_breaker

namespace deque_based {

[[nodiscard]] auto is_valid(std::u8string_view const view) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::deque<char8_t> expected{};

    for (ConstIter iter{view.cbegin()}; iter != view.cend(); ++iter)
    {
        if (char8_t const chr{*iter};
            (chr == u8')') || (chr == u8']') || (chr == u8'}'))
        {
            if (expected.empty() || expected.back() != chr)
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(map_open_to_closed(chr));
        }
    }

    return expected.empty();
}

} // namespace deque_based

namespace dyn_array_based {

/// @note Utilizes odd string circuit breaker and a dynamic array.
[[nodiscard]] auto is_valid(std::u8string_view const view) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;
    using SizeType = std::u8string_view::size_type;

    // Odd strings are always invalid.
    if ((view.size() % SizeType{2}) != SizeType{})
    {
        return false;
    }

    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
    std::unique_ptr<char8_t[]> const expected
        // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
        = std::make_unique_for_overwrite<char8_t[]>(view.size());

    assert(expected.get() != nullptr);

    char8_t* back_ptr{nullptr};
    char8_t back{};

    for (ConstIter iter{view.cbegin()}; iter != view.cend(); ++iter)
    {
        if (char8_t const chr{*iter};
            (chr == u8')') || (chr == u8']') || (chr == u8'}'))
        {
            if ((back_ptr == nullptr) || (back != chr))
            {
                return false;
            }

            if (back_ptr == expected.get())
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
            back = map_open_to_closed(chr);
            if (back_ptr == nullptr)
            {
                back_ptr = expected.get();
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

[[nodiscard]] auto is_valid(std::u8string_view const view) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::vector<char8_t> expected{};
    expected.reserve(view.size());

    for (ConstIter iter{view.cbegin()}; iter != view.cend(); ++iter)
    {
        if (char8_t const chr{*iter};
            (chr == u8')') || (chr == u8']') || (chr == u8'}'))
        {
            if (expected.empty() || expected.back() != chr)
            {
                return false;
            }

            expected.pop_back();
        }
        else
        {
            expected.push_back(map_open_to_closed(chr));
        }
    }

    return expected.empty();
}

} // namespace vector_based

namespace vector_based_demi_allocated {

[[nodiscard]] auto is_valid(std::u8string_view const view) -> bool
{
    using ConstIter = std::u8string_view::const_iterator;

    std::vector<char8_t> expected{};
    expected.reserve(view.size() / 2UZ);

    char8_t back{};
    for (ConstIter iter{view.cbegin()}; iter != view.cend(); ++iter)
    {
        if (char8_t const chr{*iter};
            (chr == u8')') || (chr == u8']') || (chr == u8'}'))
        {
            if (expected.empty() || back != chr)
            {
                return false;
            }

            expected.pop_back();

            back = expected.empty() ? char8_t{} : expected.back();
        }
        else
        {
            back = map_open_to_closed(chr);
            expected.push_back(back);
        }
    }

    return expected.empty();
}

} // namespace vector_based_demi_allocated

} // namespace forfun::valid_parentheses
