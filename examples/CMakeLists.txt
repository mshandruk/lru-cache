cmake_minimum_required(VERSION 3.16)
project(LRUCache_Examples)
add_executable(lru_cache_example main.cpp)
target_link_libraries(lru_cache_example PRIVATE LRUCache::LRUCache)