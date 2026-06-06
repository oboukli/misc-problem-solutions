// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/permutation-in-string/

#ifndef FORFUN_PERMUTATION_IN_STRING_HPP_
#define FORFUN_PERMUTATION_IN_STRING_HPP_

#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <string_view>

#include "forfun/common/concepts.hpp"
#include "forfun/common/type_traits.hpp"

namespace forfun::permutation_in_string {

namespace detail {

template <typename ScoredCharType, std::size_t Size, ScoredCharType Alpha>
    requires forfun::common::concepts::standard_char_type<ScoredCharType>
class ScoringBucket final {
public:
    static constexpr std::size_t const capacity{Size};

    using container_type = std::array<std::size_t, capacity>;

private:
    container_type container_{};

public:
    using char_type = ScoredCharType;

    using score_type = container_type::value_type;

    using reference = container_type::reference;

    using const_reference = container_type::const_reference;

    explicit constexpr ScoringBucket(
        std::basic_string_view<char_type> const s
    ) noexcept
    {
        reset_scores_internal(s);
    }

    [[nodiscard]] constexpr auto
    get_score(this auto&& self, char_type const chr) noexcept
        -> forfun::common::type_traits::reference_conditional_const_t<
            decltype(self)>
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
        return self.container_[to_index(chr)];
    }

    constexpr auto add_one(char_type const chr) noexcept -> void
    {
        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
        ++container_[to_index(chr)];
    }

    constexpr auto substract_one(char_type const chr) noexcept -> void
    {
        assert(container_[to_index(chr)] != size_type{});

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
        --container_[to_index(chr)];
    }

private:
    static constexpr char_type first_char{Alpha};

    using size_type = container_type::size_type;

    using iterator = container_type::iterator;

    constexpr auto
    reset_scores_internal(std::basic_string_view<char_type> const s) noexcept
        -> void
    {
        for (auto const chr : s)
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
            container_[to_index(chr)] = score_type{0};
        }

        for (auto const chr : s)
        {
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access,cppcoreguidelines-pro-bounds-constant-array-index)
            ++container_[to_index(chr)];
        }
    }

    [[nodiscard]] static constexpr auto to_index(char_type const chr) noexcept
        -> size_type
    {
        assert(chr >= first_char);

        return static_cast<size_type>(chr) - static_cast<size_type>(first_char);
    }
};

using Char = std::string_view::value_type;

constexpr char const first_char{'a'};
constexpr std::size_t const charset_size{26};

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
static_assert(first_char == char{97});
static_assert('z' == char{122});
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

using Bucket = ScoringBucket<Char, charset_size, first_char>;

} // namespace detail

/// @note Assumes @p haystack is not empty.
/// @note Assumes @p haystack is greater or equal in length than @p needle,
/// otherwise the behavior is undefine.
[[nodiscard]] constexpr auto check_inclusion(
    std::string_view const needle, std::string_view const haystack
) noexcept -> bool
{
    using std::size;

    using size_type = std::string_view::size_type;

    size_type const needle_size{size(needle)};

    assert(not std::empty(haystack));
    assert(size(haystack) >= needle_size);

    detail::Bucket const needle_bucket(needle);

    detail::Bucket bundle_bucket(haystack.substr(0, needle_size - 1));

    size_type const padded_end{(size(haystack) + 1) - needle_size};
    for (size_type i{}; i < padded_end; ++i)
    {
        size_type streak{};

        auto bundle{haystack.substr(i, needle_size)};

        // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
        bundle_bucket.add_one(haystack[(i + needle_size) - size_type{1}]);

        for (auto const chr : bundle)
        {
            if (needle_bucket.get_score(chr) != bundle_bucket.get_score(chr))
            {
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
                bundle_bucket.substract_one(haystack[i]);
                break;
            }

            ++streak;
        }

        if (streak == needle_size)
        {
            return true;
        }
    }

    return false;
}

namespace experimental {

/// @note Assumes @p haystack is not empty.
/// @note Assumes @p haystack is greater or equal in length than @p needle,
/// otherwise the behavior is undefine.
[[nodiscard]] constexpr auto check_inclusion(
    std::string_view const needle, std::string_view const haystack
) noexcept -> bool
{
    using std::size;

    using size_type = std::string_view::size_type;

    size_type const needle_size{size(needle)};

    assert(not std::empty(haystack));
    assert(size(haystack) >= needle_size);

    detail::Bucket const needle_bucket(needle);

    // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-avoid-unchecked-container-access)
    size_type const padded_end{(size(haystack) + size_type{1}) - needle_size};
    for (size_type i{}; i < padded_end; ++i)
    {
        size_type streak{};

        auto bundle{haystack.substr(i, needle_size)};
        detail::Bucket const bundle_bucket(bundle);

        for (auto const chr : bundle)
        {
            if (needle_bucket.get_score(chr) != bundle_bucket.get_score(chr))
            {
                break;
            }

            ++streak;
        }

        if (streak == needle_size)
        {
            return true;
        }
    }

    return false;
}

} // namespace experimental

} // namespace forfun::permutation_in_string

#endif // FORFUN_PERMUTATION_IN_STRING_HPP_
