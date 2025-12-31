#include "LRUCache.h"

#include <cstddef>
#include <optional>
#include <string>

LRUCache::LRUCache(const size_t maxSize) : maxSize_{maxSize} {}

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

    if (cache_.size() >= maxSize_) {
        const auto& [key, _] = items_.back();
        cache_.erase(key);
        items_.pop_back();
    }

    items_.emplace_front(key, value);
    cache_[key] = items_.begin();
}
