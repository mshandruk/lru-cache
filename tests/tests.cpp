#include <string>

#include <gtest/gtest.h>

#include <lru_cache/LRUCache.h>
using lru_cache::LRUCache;

TEST(LRUCacheTest, Given_FullCache_When_PutNewItem_Then_OldestIsRemoved) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");

    cache.put(3, "three");

    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_TRUE(cache.get(3).has_value());
}

TEST(LRUCacheTest, Given_DisabledCache_When_PutNewItem_Then_NotCaching) {
    LRUCache<int, std::string> cache(0);

    cache.put(1, "one");

    EXPECT_FALSE(cache.get(1).has_value());
    EXPECT_EQ(cache.size(), 0);
}

TEST(LRUCacheTest, Given_ExistItem_When_UpdateValue_Then_ReturnsUpdatedValue) {
    LRUCache<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");

    cache.put(1, "one_updated");

    EXPECT_EQ(cache.get(1).value_or(""), "one_updated");
}

TEST(LRUCacheTest, When_GetNonExistsKey_Then_ReturnsNullopt) {
    LRUCache<int, std::string> cache(3);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    EXPECT_FALSE(cache.get(4).has_value());
}

TEST(LRUCacheTest, When_GetOldestUsedItem_Then_RecentUsedKey) {
    LRUCache<int, std::string> lruCache(3);
    lruCache.put(1, "one");
    lruCache.put(2, "two");
    lruCache.put(3, "three");

    lruCache.get(1);         // should be the last recent
    lruCache.put(4, "four"); // should be the last recent

    EXPECT_FALSE(lruCache.get(2).has_value()); // should be removed
    EXPECT_TRUE(lruCache.get(1).has_value());
    EXPECT_TRUE(lruCache.get(4).has_value());
}
