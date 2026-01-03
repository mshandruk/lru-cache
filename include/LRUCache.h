#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <cstddef>
#include <list>
#include <optional>
#include <string>
#include <unordered_map>

class LRUCache {
  public:
    explicit LRUCache(size_t capacity);
    std::optional<std::string> get(int key);
    void put(int key, const std::string& value);

  private:
    size_t capacity_ = 0;
    std::list<std::pair<int, std::string>> items_;
    std::unordered_map<int, std::list<std::pair<int, std::string>>::iterator> cache_;
};

#endif // LRU_CACHE_H
