// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_LIMITS_HPP_
#define FORFUN_COMMON_LIMITS_HPP_

#include <concepts>
#include <cstddef>
#include <limits>
#include <type_traits>

namespace forfun::common::limits {

/// Calculates the cardinality of the unsigend counterpart of @p T.
template <typename T>
    requires std::integral<T>
[[nodiscard]] consteval auto domain_size() noexcept -> std::size_t
{
    using std::make_unsigned_t;
    using std::numeric_limits;

    static constexpr std::size_t const digits{
        numeric_limits<make_unsigned_t<T>>::digits
    };

    static_assert(digits <= numeric_limits<std::size_t>::digits);

    return 1UZ << digits;
}

} // namespace forfun::common::limits

#endif // FORFUN_COMMON_LIMITS_HPP_
