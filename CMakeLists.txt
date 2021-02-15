cmake_minimum_required(VERSION 3.9)

project(MiniDB VERSION 0.0.1 LANGUAGES CXX)

option(BUILD_TESTS "Build with tests" ON)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

# 源码以 UTF-8 编码保存，使用 MSVC 编译器时需要加编译参数提供支持
if(MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    message(STATUS "optional: /UTF-8")   
endif(MSVC)

include_directories(src/include)

if(BUILD_TESTS)
    add_subdirectory(test)
endif()