// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

/// Problem sources:
/// https://leetcode.com/problems/subsets/

#ifndef FORFUN_GRAPH_SUBSETS_HPP_
#define FORFUN_GRAPH_SUBSETS_HPP_

#include <vector>

namespace forfun::subsets {

[[nodiscard]] auto explode_subsets(std::vector<int> const& elements)
    -> std::vector<std::vector<int>>;

} // namespace forfun::subsets

#endif // FORFUN_GRAPH_SUBSETS_HPP_
