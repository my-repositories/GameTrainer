set(GT_TEST_TARGET_NAME test_gt_os)
project(${GT_TEST_TARGET_NAME})

add_executable(${GT_TEST_TARGET_NAME} unit_tests.cpp)

find_package (Threads)
target_link_libraries(
        ${GT_TEST_TARGET_NAME} PRIVATE
        gtest_main
#        gt_os
#        gt_xml
#        gt_lua
#        gt_core
        ${CMAKE_THREAD_LIBS_INIT}
)

#target_include_directories(
#        ${GT_PROJECT_NAME} PRIVATE
#        ${PROJECT_ROOT_DIR}/app/lib/gt_os/inc
#        ${PROJECT_ROOT_DIR}/app/lib/gt_xml/inc
#        ${PROJECT_ROOT_DIR}/app/lib/gt_lua/inc
#        ${PROJECT_ROOT_DIR}/app/lib/gt_core/inc
#)

if (MSVC)
    message('IS MSVC')
    target_compile_options(${GT_TEST_TARGET_NAME} PRIVATE /std:c++17 /W4 /WX)

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")

    # VS 2017 removed tr1
    add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
else()
    message('ISN'T MSVC')
    target_link_libraries(
            ${GT_TEST_TARGET_NAME} PRIVATE
            --coverage
    )
    target_compile_options(${GT_TEST_TARGET_NAME} PRIVATE -std=c++17 -g -Wall -Werror -Wextra -Wpedantic -Wconversion -Wswitch-default -Wswitch-enum -Wunreachable-code -Wwrite-strings -Wcast-align -Wshadow -Wundef)

    if (COVERAGE)
        target_compile_options(${GT_TEST_TARGET_NAME} PRIVATE --coverage)
    endif()
endif()
