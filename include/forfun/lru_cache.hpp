/// Problem sources:
/// https://simontoth.substack.com/p/daily-bite-of-c-lru-cache
/// https://leetcode.com/problems/lru-cache/

#ifndef FORFUN_LRU_CACHE_HPP_
#define FORFUN_LRU_CACHE_HPP_

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

    virtual int get(int const key) noexcept = 0;
    virtual void put(int const key, int const value) noexcept = 0;
};

namespace naive {

struct CacheItem {
    int key_{};
    int value_{};
    std::int64_t ticks_{0};
};

/// Least recently used (LRU) cache.
class LRUCache final : public LRUCacheBase {
public:
    explicit LRUCache(int const capacity) noexcept;

    ~LRUCache() = default;

    [[nodiscard]] int get(int const key) noexcept override;

    void put(int const key, int const value) noexcept override;

private:
    std::unique_ptr<CacheItem[]> cache_{};
    int capacity_{};
    int size_{0};
    int least_recent_idx_{0};
    std::int64_t ticks_{0};
};

} // namespace naive

namespace stl {

/// Based on a solution by Simon Toth https://compiler-explorer.com/z/8PWETEYT8
class LRUCache final : public LRUCacheBase {
public:
    explicit LRUCache(int const capacity) noexcept;

    ~LRUCache() = default;

    [[nodiscard]] int get(int const key) noexcept override;

    void put(int const key, int const value) noexcept override;

private:
    using cache_item_t = std::pair<int, int>;
    std::list<cache_item_t> cache_{};
    std::unordered_map<int, std::list<cache_item_t>::iterator> lookup_{};
    int capacity_{};
    int size_{0};
};

} // namespace stl

} // namespace forfun::lrucache

#endif // FORFUN_LRU_CACHE_HPP_
