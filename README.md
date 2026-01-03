# LRU cache

LRU Cache implementation on C++

# Project Structure

* **include/** - Header files (public API)
* **src/** - Source files (implementations)
* **tests/** - Unit tests (Google Test)
* **cmake/** - Build dependencies and configurations

# Build Instructions

### 1. Release Build

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### 2. Debug Build with Tests

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_TESTS=ON
cmake --build build
```

#### Run tests

```bash
ctest --output-on-failure --test-dir build/
```

## License

[MIT](LICENSE) © 2026 [Maxim Shandruk]
