#pragma once

#include <list>
#include <optional>
#include <unordered_map>

namespace lru_cache {
template <typename Key, typename Value>
class LRUCache {
  public:
    explicit LRUCache(std::size_t capacity);
    std::optional<Value> get(const Key& key);
    void put(const Key& key, Value value);
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t capacity() const noexcept;

  private:
    std::size_t capacity_ = 0;
    std::list<std::pair<Key, Value>> items_;
    std::unordered_map<Key, decltype(items_.begin())> cache_;
};

template <typename Key, typename Value>
LRUCache<Key, Value>::LRUCache(const std::size_t capacity)
        : capacity_{capacity} {
}

template <typename Key, typename Value>
std::optional<Value> LRUCache<Key, Value>::get(const Key& key) {
    const auto hit = cache_.find(key);
    if (hit == cache_.end()) {
        return std::nullopt;
    }
    items_.splice(items_.begin(), items_, hit->second);
    return hit->second->second;
}

template <typename Key, typename Value>
void LRUCache<Key, Value>::put(const Key& key, Value value) {
    if (capacity_ == 0) {
        return;
    }

    const auto hit = cache_.find(key);
    if (hit != cache_.end()) {
        hit->second->second = std::move(value);
        items_.splice(items_.begin(), items_, hit->second);
        return;
    }

    if (cache_.size() >= capacity_) {
        const auto oldestKey = items_.back().first;
        cache_.erase(oldestKey);
        items_.pop_back();
    }

    items_.emplace_front(key, std::move(value));
    cache_[items_.front().first] = items_.begin();
}

template <typename Key, typename Value>
std::size_t LRUCache<Key, Value>::size() const noexcept {
    return cache_.size();
}

template <typename Key, typename Value>
std::size_t LRUCache<Key, Value>::capacity() const noexcept {
    return capacity_;
}
} // namespace lru_cache
