// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_CONCEPTS_HPP_
#define FORFUN_COMMON_CONCEPTS_HPP_

#include <concepts>
#include <utility>

namespace forfun::common::concepts {

template <typename T>
concept addition_unpromoted = requires(T addend) {
    { addend + addend } -> std::same_as<T>;
};

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
