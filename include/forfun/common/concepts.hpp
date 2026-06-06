// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_CONCEPTS_HPP_
#define FORFUN_COMMON_CONCEPTS_HPP_

#include <concepts>
#include <utility>

#include "type_traits.hpp"

namespace forfun::common::concepts {

template <typename T>
concept addition_unpromoted = requires(T addend) {
    { addend + addend } -> std::same_as<T>;
};

template <typename T>
concept standard_char_type = forfun::common::type_traits::type_is_one_of_v<
    T,
    char,
    signed char,
    unsigned char,
    wchar_t,
    char8_t,
    char16_t,
    char32_t>;

template <typename Factor, typename Product>
concept multipliable_as = requires(Factor factor) {
    { factor * factor } -> std::same_as<Product>;
};

// clang-format off
template <typename Func, typename... Args>
concept noexcept_callable
    = std::invocable<Func, Args...>
    and requires(Func&& func, Args&&... args) {
        requires noexcept(func(std::forward<Args>(args)...));
    };
// clang-format on

} // namespace forfun::common::concepts

#endif // FORFUN_COMMON_CONCEPTS_HPP_
