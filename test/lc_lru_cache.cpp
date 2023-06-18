// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/lc_lru_cache.hpp"

#include <cassert>

template <typename T>
std::enable_if_t<std::is_base_of_v<forfun::lrucache::LRUCacheBase, T>, void>
test() {
    int volatile val{};

    {
        T cache{2};

        cache.put(1, 1); // Cache is {{1, 1}}.

        cache.put(2, 2); // Cache is {{1, 1, {2, 2}}.

        val = cache.get(1);
        assert(val == 1);

        cache.put(
            3, 3); // LRU key was 2. Evicts key 2. Cache is {{1, 1}, {3, 3}}.

        val = cache.get(2); // Returns -1 (key not found).
        assert(val == -1);

        cache.put(
            4, 4); // LRU key was 1; evicts key 1, cache is {{4, 4}, {3, 3}}.

        val = cache.get(1);
        assert(val == -1); // Returns -1 (key not found).

        val = cache.get(3);
        assert(val == 3);

        val = cache.get(4);
        assert(val == 4);
    }

    {
        T cache(2);

        cache.put(1, 1);

        val = cache.get(1);
        assert(val == 1);

        cache.put(2, 2);

        val = cache.get(2);
        assert(val == 2);

        cache.put(3, 3); // Evicts key 1.

        val = cache.get(1);
        assert(val == -1);

        cache.put(2, 4);

        val = cache.get(2);
        assert(val == 4);

        cache.put(4, 4); // Evicts key 3.

        val = cache.get(3);
        assert(val == -1);

        val = cache.get(5);
        assert(val == -1);
    }

    {
        T cache(1);

        cache.put(1, 1);

        val = cache.get(1);
        assert(val == 1);

        cache.put(2, 2); // Evicts key 1.

        val = cache.get(1);
        assert(val == -1);

        val = cache.get(2);
        assert(val == 2);

        cache.put(2, 3);

        val = cache.get(2);
        assert(val == 3);
    }

    {
        T cache(3);

        cache.put(1, 1);
        cache.put(2, 2);
        cache.put(3, 3);

        val = cache.get(1);
        assert(val == 1);

        val = cache.get(2);
        assert(val == 2);

        val = cache.get(3);
        assert(val == 3);

        cache.put(4, 4); // Evicts key 1.

        val = cache.get(1);
        assert(val == -1);

        val = cache.get(4);
        assert(val == 4);

        val = cache.get(2);
        assert(val == 2);

        cache.put(5, 5); // Evicts key 3, as key 2 was accessed recently.

        val = cache.get(3);
        assert(val == -1);
    }
}

int main() {
    test<forfun::lrucache::solution1::LRUCache>();
    test<forfun::lrucache::solution1::LRUCache>();

    return 0;
}
