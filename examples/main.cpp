#include <iostream>
#include <lru_cache/LRUCache.h>
#include <string>

std::string getFromDb(const int userId) {
    return "User: " + std::to_string(userId);
}

using namespace lru_cache;

int main() {
    {
        // Create cache 2 elements
        LRUCache<int, std::string> cache(2);

        // Add to cache data response
        cache.put(1, getFromDb(1));
        cache.put(2, getFromDb(2));

        // Update last recent usage (userId=1 must be last)
        cache.get(1);

        // Add to cache (userId=2 should be evicted)
        cache.put(3, getFromDb(3));

        if (const auto user3 = cache.get(3)) {
            std::cout << *user3 << " from cache\n";
        }

        if (!cache.get(2)) {
            std::cout << "User: 2 evicted from cache\n";
        }

        if (const auto user = cache.get(1)) {
            std::cout << *user << " from cache\n";
        }
    }
    {
        // Create disabled cache
        LRUCache<int, std::string> lruCache(0);
        lruCache.put(1, getFromDb(1));
        if (!lruCache.get(1)) {
            std::cout << "User: 1 not found in cache\n";
        }
    }

    return 0;
}
