# LRU cache

LRU Cache implementation on C++.

## Features

- Thread-unsafe (single-threaded use only)
- Header-only library
- Uses `std::list` and `std::unordered_map` for O(1) get/put operations
- Supports capacity = 0 (disabled cache)

# Project Structure

* **include/** - Header files (public API)
* **tests/** - Unit tests (Google Test)
* **cmake/** - Build dependencies and configurations
* examples - Examples of usage

# Usage

```c++
#include <iostream>
#include <string>

#include <lru_cache/LRUCache.h>

std::string getFromDb(const int userId) {
    return "User: " + std::to_string(userId);
}


using namespace lru_cache;

int main() {
    //Create a cache of two elements 
    LRUCache<int, std::string> cache(2); 
    // use 0 for disabling cache: LRUCache<int, std::string> lruCache(0);

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


    return 0;
}

```

### More advanced example see: [examples](examples)

# Build Instructions

### Build with Tests

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=ON
cmake --build build
```

#### Run tests

```bash
ctest --output-on-failure --test-dir build/
```

### Build Examples

```bash
cmake -B build -DBUILD_EXAMPLES=ON
cmake --build build

# Run example
./build/examples/lru_cache_example 
```

# Integration with your project

### Using CMake(FetchContent)

This is the recommended way. Add the following to your `CMakeLists.txt`:

```cmake
include(FetchContent)
FetchContent_Declare(
        LRUCache
        GIT_REPOSITORY https://github.com/mshandruk/lru-cache.git
        GIT_TAG master
)
FetchContent_MakeAvailable(LRUCache)
target_link_libraries(your_app PRIVATE LRUCache::LRUCache)
```

### Manual (header-only)

Since this is a header-only library, you can simply copy the include/lru_cache directory to your project.

1. Copy include/lru_cache/LRUCache.h to your project's include folder.
2. Add the path to your compiler's include search paths.
3. Include it in your code:

```c++
#include <lru_cache/LRUCache.h>
```

## License

[MIT](LICENSE) © 2026 Maxim Shandruk
