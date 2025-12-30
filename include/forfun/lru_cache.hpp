/// Problem sources:
/// - https://simontoth.substack.com/p/daily-bite-of-c-lru-cache
/// - https://leetcode.com/problems/lru-cache/

#ifndef FORFUN_LRU_CACHE_HPP_
#define FORFUN_LRU_CACHE_HPP_

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <list>
#include <memory>
#include <unordered_map>
#include <utility>

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

struct CacheItem final {
    std::int64_t ticks_{};
    std::size_t key_{};
    int value_{};
};

/// Least recently used (LRU) cache.
class LRUCache final {
public:
    explicit LRUCache(std::size_t capacity) noexcept;

    LRUCache(LRUCache const&) noexcept = delete;

    LRUCache(LRUCache&&) noexcept = delete;

    ~LRUCache() noexcept = default;

    auto operator=(LRUCache const&) noexcept -> LRUCache& = delete;

    auto operator=(LRUCache&&) noexcept -> LRUCache& = delete;

    [[nodiscard]] auto get(std::size_t key) noexcept -> int;

    auto put(std::size_t key, int value) noexcept -> void;

private:
    // NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
    std::unique_ptr<CacheItem[]> cache_;
    std::size_t capacity_{};
    std::size_t size_{};
    std::size_t least_recent_idx_{};
    std::int64_t ticks_{};
};

} // namespace naive

namespace stl {

/// @remark Based on a solution by Simon Toth
/// https://compiler-explorer.com/z/8PWETEYT8.
class LRUCache final {
public:
    explicit LRUCache(std::size_t capacity);

    LRUCache(LRUCache const&) = delete;

    LRUCache(LRUCache&&) noexcept = delete;

    ~LRUCache() noexcept = default;

    auto operator=(LRUCache const&) noexcept -> LRUCache& = delete;

    auto operator=(LRUCache&&) noexcept -> LRUCache& = delete;

    [[nodiscard]] auto get(std::size_t key) noexcept -> int;

    auto put(std::size_t key, int value) -> void;

private:
    using cache_item_t = std::pair<std::size_t, int>;
    std::list<cache_item_t> cache_;
    std::unordered_map<std::size_t, std::list<cache_item_t>::iterator> lookup_;
    std::size_t capacity_{};
    std::size_t size_{};
};

} // namespace stl

} // namespace forfun::lrucache

#endif // FORFUN_LRU_CACHE_HPP_
