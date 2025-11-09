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
concept addition_unpromoted = requires(T v) {
    { v + v } -> std::same_as<T>;
};

template <typename T, typename U>
concept multipliable_as = requires(T v) {
    { v * v } -> std::same_as<U>;
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
