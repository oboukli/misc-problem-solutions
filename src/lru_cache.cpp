// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/lru_cache.hpp"

#include <cassert>

namespace forfun::lrucache {

namespace naive {

LRUCache::LRUCache(int const capacity) noexcept :
    capacity_{capacity}, cache_{std::make_unique<CacheItem[]>(capacity)} {
}

[[nodiscard]] int LRUCache::get(int const key) noexcept {
    int result{-1};
    std::int64_t lowest_tick_count{ticks_};

    int i{0};
    for (; i < size_; ++i) {
        if (cache_[i].key_ == key) {
            result = cache_[i].value_;
            cache_[i].ticks_ = ticks_;
            break;
        }
        if (lowest_tick_count >= cache_[i].ticks_) {
            lowest_tick_count = cache_[i].ticks_;
            least_recent_idx_ = i;
        }
    }

    for (; i < size_; ++i) {
        if (lowest_tick_count >= cache_[i].ticks_) {
            lowest_tick_count = cache_[i].ticks_;
            least_recent_idx_ = i;
        }
    }

    ++ticks_;

    return result;
}

void LRUCache::put(int const key, int const value) noexcept {
    assert(size_ <= capacity_);

    for (int i{0}; i < size_; ++i) {
        if (cache_[i].key_ == key) {
            cache_[i].value_ = value;

            return;
        }
    }

    if (size_ < capacity_) {
        cache_[size_].key_ = key;
        cache_[size_].value_ = value;
        cache_[size_].ticks_ = ticks_;

        ++size_;

        return;
    }

    cache_[least_recent_idx_].key_ = key;
    cache_[least_recent_idx_].value_ = value;
    cache_[least_recent_idx_].ticks_ = ticks_;
}

} // namespace naive

namespace stl {

LRUCache::LRUCache(int const capacity) noexcept : capacity_{capacity} {
    lookup_.reserve(capacity);
}

[[nodiscard]] int LRUCache::get(int const key) noexcept {
    auto const existing_key_iter{lookup_.find(key)};
    if (existing_key_iter == lookup_.end()) {
        return -1;
    }

    cache_.splice(cache_.end(), cache_, existing_key_iter->second);

    return existing_key_iter->second->second;
}

void LRUCache::put(int const key, int const value) noexcept {
    assert(size_ <= capacity_);
    assert(size_ == lookup_.size());
    assert(size_ == cache_.size());

    // Update if key exists.
    auto const iter_existing_key{lookup_.find(key)};
    if (iter_existing_key != lookup_.end()) {
        iter_existing_key->second->second = value;

        return;
    }

    // Add new if cache is not full.
    auto const cache_end{cache_.end()};
    if (size_ < capacity_) {
        auto const emplaced_key_iter{cache_.emplace(cache_end, key, value)};
        assert(cache_.end() == cache_end);
        [[maybe_unused]] auto const new_key_insert_result{
            lookup_.insert({key, emplaced_key_iter})};
        assert(new_key_insert_result.second);
        ++size_;

        return;
    }

    // Replace oldest key if cache is full.
    [[maybe_unused]] auto const num_elements_removed{
        lookup_.erase(cache_.begin()->first)};
    assert(num_elements_removed == 1);
    cache_.splice(cache_end, cache_, cache_.begin());
    [[maybe_unused]] auto const replacement_key_insert_result{
        lookup_.insert({key, std::prev(cache_end)})};
    assert(replacement_key_insert_result.second);
    assert(cache_.end() == cache_end);
    cache_.back().first = key;
    cache_.back().second = value;
}

} // namespace stl

} // namespace forfun::lrucache
