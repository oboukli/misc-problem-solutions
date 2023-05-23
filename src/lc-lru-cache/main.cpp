/// Problem sources:
/// https://simontoth.substack.com/p/daily-bite-of-c-lru-cache
/// https://leetcode.com/problems/lru-cache/

#include <cassert>
#include <cstdint>
#include <iterator>
#include <list>
#include <memory>
#include <unordered_map>

namespace forfun::lrucache {

class LRUCacheBase {
public:
    virtual ~LRUCacheBase() {
    }
    virtual int get(const int key) noexcept = 0;
    virtual void put(const int key, const int value) noexcept = 0;
};

namespace solution1 {

struct CacheItem {
    int key_{};
    int value_{};
    std::int64_t ticks_{0};
};

/// Least recently used (LRU) cache.
class LRUCache final : public LRUCacheBase {
public:
    explicit LRUCache(const int capacity) noexcept :
        capacity_{capacity}, cache_{std::make_unique<CacheItem[]>(capacity)} {
    }

    ~LRUCache() = default;

    [[nodiscard]] int get(const int key) noexcept override {
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

    void put(const int key, const int value) noexcept override {
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

private:
    std::unique_ptr<CacheItem[]> cache_{};
    int capacity_{};
    int size_{0};
    int least_recent_idx_{0};
    std::int64_t ticks_{0};
};

} // namespace solution1

namespace solution2 {

/// Based on a solution by Simon Toth https://compiler-explorer.com/z/8PWETEYT8
class LRUCache final : public LRUCacheBase {
public:
    explicit LRUCache(const int capacity) noexcept : capacity_{capacity} {
        lookup_.reserve(capacity);
    }

    ~LRUCache() = default;

    [[nodiscard]] int get(const int key) noexcept override {
        const auto existing_key_iter{lookup_.find(key)};
        if (existing_key_iter == lookup_.end()) {
            return -1;
        }

        cache_.splice(cache_.end(), cache_, existing_key_iter->second);

        return existing_key_iter->second->second;
    }

    void put(const int key, const int value) noexcept override {
        assert(size_ <= capacity_);
        assert(size_ == lookup_.size());
        assert(size_ == cache_.size());

        // Update if key exists.
        const auto iter_existing_key{lookup_.find(key)};
        if (iter_existing_key != lookup_.end()) {
            iter_existing_key->second->second = value;

            return;
        }

        // Add new if cache is not full.
        const auto cache_end{cache_.end()};
        if (size_ < capacity_) {
            const auto emplaced_key_iter{cache_.emplace(cache_end, key, value)};
            assert(cache_.end() == cache_end);
            [[maybe_unused]] const auto new_key_insert_result{
                lookup_.insert({key, emplaced_key_iter})};
            assert(new_key_insert_result.second);
            ++size_;

            return;
        }

        // Replace oldest key if cache is full.
        [[maybe_unused]] const auto num_elements_removed{
            lookup_.erase(cache_.begin()->first)};
        assert(num_elements_removed == 1);
        cache_.splice(cache_end, cache_, cache_.begin());
        [[maybe_unused]] const auto replacement_key_insert_result{
            lookup_.insert({key, std::prev(cache_end)})};
        assert(replacement_key_insert_result.second);
        assert(cache_.end() == cache_end);
        cache_.back().first = key;
        cache_.back().second = value;
    }

private:
    using cache_item_t = std::pair<int, int>;
    std::list<cache_item_t> cache_{};
    std::unordered_map<int, std::list<cache_item_t>::iterator> lookup_{};
    int capacity_{};
    int size_{0};
};

} // namespace solution2

} // namespace forfun::lrucache

template <typename T>
std::enable_if_t<std::is_base_of_v<forfun::lrucache::LRUCacheBase, T>, void>
test() {
    volatile int val{};

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
