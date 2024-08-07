// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem source:
/// https://leetcode.com/problems/concatenation-of-array/description/

#ifndef FORFUN_ARRAY_CONCATENATION_HPP_
#define FORFUN_ARRAY_CONCATENATION_HPP_

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>

namespace forfun::array_concatenation {

namespace functional {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, std::size_t{2U * Size}>& dest
) noexcept -> void
{
    std::copy(src.cbegin(), src.cend(), dest.begin());
    std::copy(src.cbegin(), src.cend(), std::next(dest.begin(), Size));
}

} // namespace functional

namespace functional_minimal {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, std::size_t{2U * Size}>& dest
) noexcept -> void
{
    std::copy(src.cbegin(), src.cend(), dest.begin());
    std::copy(src.cbegin(), src.cend(), dest.begin() + Size);
}

} // namespace functional_minimal

namespace iterator_based {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, std::size_t{2U * Size}>& dest
) noexcept -> void
{
    auto const src_cbegin{src.cbegin()};
    auto const src_cend{src.cend()};
    auto const dest_begin{dest.begin()};
    for (std::size_t i{0U}; i < 2U; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        auto itr{dest_begin + (Size * i)};
        for (auto src_itr{src_cbegin}; src_itr != src_cend; ++src_itr)
        {
            *(itr++) = *src_itr;
        }
    }
}

} // namespace iterator_based

namespace iterator_based_double {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, std::size_t{2U * Size}>& dest
) noexcept -> void
{
    auto const src_cbegin{src.cbegin()};
    auto const src_cend{src.cend()};
    auto const dest_begin{dest.begin()};

    {
        auto itr{dest_begin};
        for (auto src_itr{src_cbegin}; src_itr != src_cend; ++src_itr)
        {
            *(itr++) = *src_itr;
        }
    }
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        auto itr{dest_begin + Size};
        for (auto src_itr{src_cbegin}; src_itr != src_cend; ++src_itr)
        {
            *(itr++) = *src_itr;
        }
    }
}

} // namespace iterator_based_double

namespace iterator_unfolded {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, std::size_t{2U * Size}>& dest
) noexcept -> void
{
    auto const src_cend{src.cend()};
    auto dest1_itr{dest.begin()};
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto dest2_itr{dest1_itr + Size};
    for (auto src_itr{src.cbegin()}; src_itr != src_cend; ++src_itr)
    {
        *(dest1_itr++) = *src_itr;
        *(dest2_itr++) = *src_itr;
    }
}

} // namespace iterator_unfolded

namespace nested_loops {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, std::size_t{2U * Size}>& dest
) noexcept -> void
{
    for (std::size_t i{0U}; i < 2U; ++i)
    {
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable : 6294)
#endif // _MSC_VER
        for (std::size_t j{0U}; j < Size; ++j)
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
            dest[j + (i * Size)] = src[j];
        }
#if _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
    }
}

} // namespace nested_loops

namespace semi_unfolded {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, std::size_t{2U * Size}>& dest
) noexcept -> void
{
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable : 6294)
#endif // _MSC_VER
    for (std::size_t i{0U}; i < Size; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        dest[i] = src[i];
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        dest[i + Size] = src[i];
    }
#if _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
}

} // namespace semi_unfolded

} // namespace forfun::array_concatenation

#endif // FORFUN_ARRAY_CONCATENATION_HPP_
