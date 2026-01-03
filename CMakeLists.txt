cmake_minimum_required(VERSION 3.16)
project(LRUCache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(LIB_NAME lru_cache)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/cpp-infra/cmake")
include(DevTools)
add_dev_tools_targets(
        INFRA_DIR "${CMAKE_SOURCE_DIR}/external/cpp-infra"
        CHECK_DIRS "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/include" "${CMAKE_SOURCE_DIR}/tests"
)

add_library(${PROJECT_NAME} STATIC
        src/LRUCache.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${LIB_NAME})

option(LRU_CACHE_ENABLE_TESTS "Enable google test" OFF)

if (DEFINED ENABLE_TESTS)
    set(LRU_CACHE_ENABLE_TESTS ${ENABLE_TESTS} CACHE BOOL "Enable google test" FORCE)
endif ()

if (LRU_CACHE_ENABLE_TESTS)
    enable_testing()
    include(cmake/Dependencies.cmake)
    add_subdirectory(tests)
endif ()
