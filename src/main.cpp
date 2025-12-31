#include <LRUCache.h>
#include <cassert>

int main() {
    LRUCache lruCache(10);
    lruCache.put(20250401, "db1");
    const auto result = lruCache.get(20250401);
    assert(result.has_value());
    assert(result.value() == "db1");
    return 0;
}
