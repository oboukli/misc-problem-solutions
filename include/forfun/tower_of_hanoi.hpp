// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://en.wikipedia.org/wiki/Tower_of_Hanoi

#ifndef FORFUN_TOWER_OF_HANOI_HPP_
#define FORFUN_TOWER_OF_HANOI_HPP_

#include <concepts>

namespace forfun::tower_of_hanoi::recursive {

/// @note Time complexity: \f$O(2^n)\f$
/// @note Space complexity: \f$O(n)\f$
template <typename Rod, typename Monk, typename CountType>
    requires std::invocable<Monk, Rod&, Rod&> and std::integral<CountType>
constexpr auto toh(
    Rod& src, Rod& des, Rod& aux, Monk monk, CountType num_disks
) noexcept(noexcept(monk(src, des))) -> void
{
    if (num_disks == CountType{}) [[unlikely]]
    {
        return;
    }

    --num_disks;

    toh(src, aux, des, monk, num_disks);
    monk(src, des);
    toh(aux, des, src, monk, num_disks);
}

} // namespace forfun::tower_of_hanoi::recursive

#endif // FORFUN_TOWER_OF_HANOI_HPP_
