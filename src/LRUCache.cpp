#include "LRUCache.h"

#include <cstddef>
#include <optional>
#include <string>

LRUCache::LRUCache(const size_t capacity) : capacity_{capacity} {}

std::optional<std::string> LRUCache::get(const int key) {
    const auto hit = cache_.find(key);
    if (hit == cache_.end()) {
        return std::nullopt;
    }

    items_.splice(items_.begin(), items_, hit->second);
    return hit->second->second;
}

void LRUCache::put(int key, const std::string& value) {
    if (const auto hit = cache_.find(key); hit != cache_.end()) {
        hit->second->second = value;
        items_.splice(items_.begin(), items_, hit->second);
        return;
    }

    if (cache_.size() >= capacity_) {
        const auto& [key, _] = items_.back();
        cache_.erase(key);
        items_.pop_back();
    }

    items_.emplace_front(key, value);
    cache_[key] = items_.begin();
}

std::size_t LRUCache::size() const noexcept {
    return cache_.size();
}

std::size_t LRUCache::capacity() const noexcept {
    return capacity_;
}
