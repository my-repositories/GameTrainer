function(INIT_TEST TEST_TARGET_NAME)
    project(${GT_TEST_TARGET_NAME})

    file(GLOB_RECURSE GT_TEST_SOURCES src/*.cpp)
    add_executable(${GT_TEST_TARGET_NAME} ${GT_TEST_SOURCES})
    add_test(${GT_TEST_TARGET_NAME} ${GT_TEST_TARGET_NAME})

    find_package(Threads)
    target_link_libraries(
        ${GT_TEST_TARGET_NAME} PRIVATE
        gtest_main
        ${CMAKE_THREAD_LIBS_INIT}
    )
endfunction()
