set(TEST_TARGET lru_cache_tests)
add_executable(${TEST_TARGET}
        tests.cpp
)

target_link_libraries(${TEST_TARGET}
        PRIVATE
        LRUCache::LRUCache
        GTest::gtest_main
        GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})
