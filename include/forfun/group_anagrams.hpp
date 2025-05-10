// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/group-anagrams/

#ifndef FORFUN_GROUP_ANAGRAMS_HPP_
#define FORFUN_GROUP_ANAGRAMS_HPP_

#include <array>
#include <concepts>
#include <cstddef>
#include <iterator>
#include <string>
#include <vector>

namespace forfun::group_anagrams {

namespace detail {

constexpr std::string::value_type const first_char{'a'};
constexpr std::string::value_type const last_char{'z'};

static_assert(
    (last_char - first_char) == 25,
    "Basic assumption about the compile-time character encoding standard must "
    "hold"
);
constexpr std::size_t const bucket_size{(last_char - first_char) + 1UZ};

template <std::input_iterator Iter, std::sentinel_for<Iter> Sentinel>
constexpr auto fill_bucket(Iter iter, Sentinel const last) noexcept
    -> std::array<std::size_t, detail::bucket_size>
{
    std::array<std::size_t, detail::bucket_size> bucket{};
    for (; iter != last; ++iter)
    {
        ++(*std::next(bucket.begin(), (*iter) - first_char));
    }

    return bucket;
}

} // namespace detail

template <std::forward_iterator Iter, std::sentinel_for<Iter> Sentinel>
    requires std::convertible_to<std::iter_value_t<Iter>, std::string>
[[nodiscard]] auto group_anagrams(Iter iter, Sentinel const last)
    -> std::vector<std::vector<std::string>>
{
    std::vector<std::vector<std::string>> result{{*iter}};

    std::vector<std::array<std::size_t, detail::bucket_size>> buckets{};
    buckets.emplace_back(detail::fill_bucket(iter->cbegin(), iter->cend()));

    while (++iter != last)
    {
        std::array<std::size_t, detail::bucket_size> bucket{
            detail::fill_bucket(iter->cbegin(), iter->cend())
        };

        std::size_t bucket_idx{};
        for (; bucket_idx != buckets.size(); ++bucket_idx)
        {
            std::size_t i{};
            for (; i < detail::bucket_size; ++i)
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
                if (bucket[i] != buckets[bucket_idx][i])
                {
                    break;
                }
            }

            if (i == detail::bucket_size)
            {
                result[bucket_idx].emplace_back(*iter);
                break;
            }
        }

        if (bucket_idx == buckets.size())
        {
            buckets.emplace_back(bucket);
            result.emplace_back(std::vector{*iter});
        }
    }

    return result;
}

} // namespace forfun::group_anagrams

#endif // FORFUN_GROUP_ANAGRAMS_HPP_
