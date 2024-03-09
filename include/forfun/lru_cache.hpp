/// Problem sources:
/// https://simontoth.substack.com/p/daily-bite-of-c-lru-cache
/// https://leetcode.com/problems/lru-cache/

#ifndef FORFUN_LRU_CACHE_HPP_
#define FORFUN_LRU_CACHE_HPP_

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <list>
#include <memory>
#include <unordered_map>

namespace forfun::lrucache {

namespace concepts {

template <typename T>
concept lru_cache = requires(T cache, std::size_t k, int v) {
    { T(k) } -> std::same_as<T>;
    { cache.put(k, v) } -> std::same_as<void>;
    { cache.get(k) } -> std::same_as<int>;
};

} // namespace concepts

namespace naive {

struct CacheItem {
    std::size_t key_{};
    int value_{};
    std::int64_t ticks_{0};
};

/// Least recently used (LRU) cache.
class LRUCache final {
public:
    explicit LRUCache(std::size_t const capacity) noexcept;

    [[nodiscard]] int get(std::size_t const key) noexcept;

    void put(std::size_t const key, int const value) noexcept;

private:
    std::unique_ptr<CacheItem[]> cache_{};
    std::size_t capacity_{0};
    std::size_t size_{0};
    std::size_t least_recent_idx_{0};
    std::int64_t ticks_{0};
};

} // namespace naive

namespace stl {

/// Based on a solution by Simon Toth https://compiler-explorer.com/z/8PWETEYT8
class LRUCache final {
public:
    explicit LRUCache(std::size_t const capacity) noexcept;

    ~LRUCache() = default;

    [[nodiscard]] int get(std::size_t const key) noexcept;

    void put(std::size_t const key, int const value) noexcept;

private:
    using cache_item_t = std::pair<std::size_t, int>;
    std::list<cache_item_t> cache_{};
    std::unordered_map<std::size_t, std::list<cache_item_t>::iterator>
        lookup_{};
    std::size_t capacity_{0};
    std::size_t size_{0};
};

} // namespace stl

} // namespace forfun::lrucache

#endif // FORFUN_LRU_CACHE_HPP_
