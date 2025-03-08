// Copyright (c) Omar Boukli-Hacene. All rights reserved.
// Distributed under an MIT-style license that can be
// found in the LICENSE file.

// SPDX-License-Identifier: MIT

#include "forfun/lru_cache.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>

namespace forfun::lrucache {

namespace naive {

LRUCache::LRUCache(std::size_t const capacity) noexcept :
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
    cache_{std::make_unique<CacheItem[]>(capacity)}, capacity_{capacity}
{
}

[[nodiscard]] auto LRUCache::get(std::size_t const key) noexcept -> int
{
    int result{-1};
    std::int64_t lowest_tick_count{ticks_};

    std::size_t i{0U};
    for (; i < size_; ++i)
    {
        if (cache_[i].key_ == key)
        {
            result = cache_[i].value_;
            cache_[i].ticks_ = ticks_;
            break;
        }
        if (lowest_tick_count >= cache_[i].ticks_)
        {
            lowest_tick_count = cache_[i].ticks_;
            least_recent_idx_ = i;
        }
    }

    for (; i < size_; ++i)
    {
        if (lowest_tick_count >= cache_[i].ticks_)
        {
            lowest_tick_count = cache_[i].ticks_;
            least_recent_idx_ = i;
        }
    }

    ++ticks_;

    return result;
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
auto LRUCache::put(std::size_t const key, int const value) noexcept -> void
{
    assert(size_ <= capacity_);

    for (std::size_t i{0U}; i < size_; ++i)
    {
        if (cache_[i].key_ == key)
        {
            cache_[i].value_ = value;

            return;
        }
    }

    if (size_ < capacity_)
    {
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

LRUCache::LRUCache(std::size_t const capacity) noexcept : capacity_{capacity}
{
    lookup_.reserve(capacity);
}

[[nodiscard]] auto LRUCache::get(std::size_t const key) noexcept -> int
{
    auto const existing_key_iter{lookup_.find(key)};
    if (existing_key_iter == lookup_.end())
    {
        return -1;
    }

    cache_.splice(cache_.end(), cache_, existing_key_iter->second);

    return existing_key_iter->second->second;
}

auto LRUCache::put(std::size_t const key, int const value) noexcept -> void
{
    assert(size_ <= capacity_);
    assert(size_ == lookup_.size());
    assert(size_ == cache_.size());

    // Update if key exists.
    if (auto const iter_existing_key{lookup_.find(key)};
        iter_existing_key != lookup_.end())
    {
        iter_existing_key->second->second = value;

        return;
    }

    // Add new if cache is not full.
    if (size_ < capacity_)
    {
        auto const emplaced_key_iter{cache_.emplace(cache_.end(), key, value)};
        [[maybe_unused]] auto const new_key_insert_result{
            lookup_.insert({key, emplaced_key_iter})
        };
        assert(new_key_insert_result.second);
        ++size_;

        return;
    }

    // Replace oldest key if cache is full.
    [[maybe_unused]] auto const num_elements_removed{
        lookup_.erase(cache_.begin()->first)
    };
    assert(num_elements_removed == 1U);
    cache_.splice(cache_.end(), cache_, cache_.begin());
    [[maybe_unused]] auto const replacement_key_insert_result{
        lookup_.insert({key, std::prev(cache_.end())})
    };
    assert(replacement_key_insert_result.second);
    cache_.back().first = key;
    cache_.back().second = value;
}

} // namespace stl

} // namespace forfun::lrucache
