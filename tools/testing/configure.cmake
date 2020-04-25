function(CONFIGURE_TEST TEST_TARGET_NAME)
    if (GT_OS STREQUAL "win")
        message('IS MSVC')
        target_compile_options(${TEST_TARGET_NAME} PRIVATE /std:c++17 /W4 /WX)

        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Ox")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od")

        # VS 2017 removed tr1
        add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
    else()
        message('ISN'T MSVC')
        target_compile_options(
            ${TEST_TARGET_NAME} PRIVATE
            -std=c++17
            -g
            -Wall
            -Werror
            -Wextra
            -Wpedantic
            -Wconversion
            -Wswitch-default
            -Wswitch-enum
            -Wunreachable-code
            -Wwrite-strings
            -Wcast-align
            -Wshadow
            -Wundef
        )

        if(COVERAGE)
            target_link_libraries(${TEST_TARGET_NAME} PRIVATE --coverage)
            target_compile_options(${TEST_TARGET_NAME} PRIVATE --coverage)
        endif()
    endif()
endfunction()
