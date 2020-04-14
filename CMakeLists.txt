cmake_minimum_required(VERSION 3.15)

project(clang_travis_cmake_gtest_coveralls_example)
set(CMAKE_C_STANDARD 99) # or delete it?
set(CMAKE_CXX_STANDARD 17)
include(gtest.cmake)

SET(COVERAGE OFF CACHE BOOL "Coverage")

add_executable(tests unit_tests.cpp)

find_package (Threads)
target_link_libraries(
        tests PRIVATE
        gtest
        --coverage
        ${CMAKE_THREAD_LIBS_INIT}
)

if (MSVC)
    message('IS MSVC')
    target_compile_options(tests PRIVATE /std:c++17 /W4 /WX)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")

    # VS 2017 removed tr1
    add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
else()
    message('ISN'T MSVC')
    target_compile_options(tests PRIVATE -std=c++14 -g -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef)

    if (COVERAGE)
        target_compile_options(tests PRIVATE --coverage)
    endif()
endif()
