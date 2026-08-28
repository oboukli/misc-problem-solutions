// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/longest-substring-without-repeating-characters/

#ifndef FORFUN_SEQUENCE_LONGEST_NON_REPEATING_SUBSTRING_HPP_
#define FORFUN_SEQUENCE_LONGEST_NON_REPEATING_SUBSTRING_HPP_

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstring>
#include <iterator>
#include <string_view>

namespace forfun::longest_non_repeating_substring {

namespace index_based {

/// @note @p str must be a non-empty string, otherwise the behavior is
/// undefined.
[[nodiscard]] constexpr auto
longest_unique_substring_length(std::string_view str) noexcept -> std::size_t
{
    static constexpr std::size_t const num_buckets{128};

    using BucketsType = std::array<std::size_t, num_buckets>;
    using SizeType = BucketsType::size_type;

    std::size_t max_len{1};
    BucketsType buckets{};

    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)

    ++buckets[static_cast<SizeType>(str.front())];

    for (std::size_t idx_a{}, idx_b = 1UZ; idx_b < str.size(); ++idx_b)
    {
        auto const chr_idx_b{static_cast<SizeType>(str[idx_b])};
        ++buckets[chr_idx_b];
        while (buckets[chr_idx_b] != 1U)
        {
            --buckets[static_cast<SizeType>(str[idx_a])];
            ++idx_a;
        }

        max_len = std::max(max_len, (idx_b - idx_a) + 1UZ);
    }

    // NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)

    return max_len;
}

} // namespace index_based

namespace iterator_based {

/// @note @p str must be a non-empty string, otherwise the behavior is
/// undefined.
[[nodiscard]] constexpr auto
longest_unique_substring_length(std::string_view const str) noexcept
    -> std::size_t
{
    static constexpr std::size_t const num_buckets{128};

    using BucketsType = std::array<std::size_t, num_buckets>;
    using SizeType = BucketsType::size_type;

    std::size_t max_len{1};
    BucketsType buckets{};

    auto iter_a{str.cbegin()};

    // NOLINTBEGIN(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)

    ++buckets[static_cast<SizeType>(str.front())];

    for (auto iter_b{std::next(str.cbegin())}; iter_b != str.cend(); ++iter_b)
    {
        auto const chr_idx_b{static_cast<SizeType>(*iter_b)};
        ++buckets[chr_idx_b];
        while (buckets[chr_idx_b] != 1UZ)
        {
            --buckets[static_cast<SizeType>(*iter_a)];

            ++iter_a;
        }

        max_len = std::max(
            static_cast<std::size_t>(iter_b - iter_a) + 1UZ, max_len
        );
    }

    // NOLINTEND(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)

    return max_len;
}

} // namespace iterator_based

} // namespace forfun::longest_non_repeating_substring

#endif // FORFUN_SEQUENCE_LONGEST_NON_REPEATING_SUBSTRING_HPP_
