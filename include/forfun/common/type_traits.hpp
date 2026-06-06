// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#ifndef FORFUN_COMMON_TYPE_TRAITS_HPP_
#define FORFUN_COMMON_TYPE_TRAITS_HPP_

#include <type_traits>

namespace forfun::common::type_traits {

template <typename T>
using reference_conditional_const_t = std::conditional_t<
    std::is_const_v<std::remove_reference_t<T>>,
    typename std::remove_reference_t<T>::const_reference,
    typename std::remove_reference_t<T>::reference>;

template <typename T, typename... Ts>
constexpr bool const type_is_one_of_v
    = std::disjunction_v<std::is_same<T, Ts>...>;

} // namespace forfun::common::type_traits

#endif // FORFUN_COMMON_TYPE_TRAITS_HPP_
