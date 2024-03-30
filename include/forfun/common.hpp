// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_HPP_
#define FORFUN_COMMON_HPP_

#include <concepts>

namespace forfun::common::concepts {

template <typename T>
concept addition_unpromoted = std::integral<T> and requires(T n) {
    { n + n } -> std::same_as<T>;
};

} // namespace forfun::common::concepts

#endif // FORFUN_COMMON_HPP_
