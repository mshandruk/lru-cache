cmake_minimum_required(VERSION 3.16)
project(LRUCache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(LRU_CACHE_IS_ROOT_PROJECT ON)
endif ()

if (LRU_CACHE_IS_ROOT_PROJECT)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/cpp-infra/cmake")
    include(DevTools OPTIONAL RESULT_VARIABLE DEVTOOLS_FOUND)
    if (DEVTOOLS_FOUND)
        add_dev_tools_targets(
                INFRA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/cpp-infra"
                CHECK_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/tests"
        )
    endif ()
endif ()

add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
        INTERFACE
        compile_options
)

target_include_directories(${PROJECT_NAME}
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

option(LRU_CACHE_ENABLE_TESTS "Enable tests for LRUCache" OFF)
option(LRU_CACHE_BUILD_EXAMPLES "Build examples for LRUCache" OFF)

if (DEFINED ENABLE_TESTS)
    set(LRU_CACHE_ENABLE_TESTS ${ENABLE_TESTS} CACHE BOOL "Build tests" FORCE)
endif ()

if (DEFINED BUILD_EXAMPLES)
    set(LRU_CACHE_BUILD_EXAMPLES ${BUILD_EXAMPLES} CACHE BOOL "Build examples" FORCE)
endif ()


if (LRU_CACHE_ENABLE_TESTS)
    enable_testing()
    include(cmake/Dependencies.cmake)
    add_subdirectory(tests)
endif ()

if (LRU_CACHE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()