// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/concatenation-of-array/

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
    std::array<T, Size> const& src, std::array<T, 2UZ * Size>& dest
) noexcept -> void
{
    std::copy(src.cbegin(), src.cend(), dest.begin());
    std::copy(src.cbegin(), src.cend(), std::next(dest.begin(), Size));
}

} // namespace functional

namespace functional_minimal {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, 2UZ * Size>& dest
) noexcept -> void
{
    std::copy(src.cbegin(), src.cend(), dest.begin());
    std::copy(src.cbegin(), src.cend(), dest.begin() + Size);
}

} // namespace functional_minimal

namespace iterator_based {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, 2UZ * Size>& dest
) noexcept -> void
{
    for (std::size_t i{0UZ}; i < 2UZ; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        auto iter{dest.begin() + (Size * i)};
        for (auto src_iter{src.cbegin()}; src_iter != src.cend(); ++src_iter)
        {
            *(iter++) = *src_iter;
        }
    }
}

} // namespace iterator_based

namespace iterator_based_double {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, 2UZ * Size>& dest
) noexcept -> void
{
    {
        auto iter{dest.begin()};
        for (auto src_iter{src.cbegin()}; src_iter != src.cend(); ++src_iter)
        {
            *(iter++) = *src_iter;
        }
    }
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        auto iter{dest.begin() + Size};
        for (auto src_iter{src.cbegin()}; src_iter != src.cend(); ++src_iter)
        {
            *(iter++) = *src_iter;
        }
    }
}

} // namespace iterator_based_double

namespace iterator_unfolded {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, 2UZ * Size>& dest
) noexcept -> void
{
    auto dest1_iter{dest.begin()};
    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    auto dest2_iter{dest1_iter + Size};
    for (auto src_iter{src.cbegin()}; src_iter != src.cend(); ++src_iter)
    {
        *(dest1_iter++) = *src_iter;
        *(dest2_iter++) = *src_iter;
    }
}

} // namespace iterator_unfolded

namespace nested_loops {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, 2UZ * Size>& dest
) noexcept -> void
{
    for (std::size_t i{0UZ}; i < 2UZ; ++i)
    {
#ifdef _MSC_VER
// Disable LOOP_BODY_NEVER_EXECUTED code analysis
#pragma warning(push)
#pragma warning(disable : 6294)
#endif // _MSC_VER
        for (std::size_t j{0UZ}; j < Size; ++j)
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
            dest[j + (i * Size)] = src[j];
        }
#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
    }
}

} // namespace nested_loops

namespace semi_unfolded {

template <typename T, std::size_t Size>
constexpr auto concatenate(
    std::array<T, Size> const& src, std::array<T, 2UZ * Size>& dest
) noexcept -> void
{
#ifdef _MSC_VER
// Disable LOOP_BODY_NEVER_EXECUTED code analysis
#pragma warning(push)
#pragma warning(disable : 6294)
#endif // _MSC_VER
    for (std::size_t i{0UZ}; i < Size; ++i)
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        dest[i] = src[i];
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
        dest[i + Size] = src[i];
    }
#ifdef _MSC_VER
#pragma warning(pop)
#endif // _MSC_VER
}

} // namespace semi_unfolded

} // namespace forfun::array_concatenation

#endif // FORFUN_ARRAY_CONCATENATION_HPP_
