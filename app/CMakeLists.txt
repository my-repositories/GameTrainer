set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(MY_APP_TARGET ${MY_PROJECT_NAME}-${MY_PROJECT_VERSION}-${MY_PLATFORM}-${MY_TOOLCHAIN})

file(GLOB MY_APP_SOURCES "src/*.cpp")
file(GLOB MY_APP_HEADERS "inc/*.hpp")
add_executable(${MY_APP_TARGET} ${MY_APP_HEADERS} ${MY_APP_SOURCES})

target_include_directories(
        ${MY_APP_TARGET} PRIVATE
        ${PROJECT_ROOT_DIR}/app/inc
        ${PROJECT_ROOT_DIR}/deps/inc/lua-5.3.4
        ${PROJECT_ROOT_DIR}/mylib/inc
)

set_target_properties(
        ${MY_APP_TARGET} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_definitions(
        ${MY_APP_TARGET} PRIVATE
        MY_PROJECT_VERSION="${MY_PROJECT_VERSION}"
)

target_link_directories(
        ${MY_APP_TARGET} PRIVATE
        ${PROJECT_ROOT_DIR}/deps/lib
)

include(../tools/find_lib.cmake)
FIND_LIB(LIBWMM "winmm.lib")
message(STATUS "LIBWMM: ${LIBWMM}")

target_link_libraries(
        ${MY_APP_TARGET} PRIVATE
        ${MY_LIBRARY_NAME}
        ${PROJECT_ROOT_DIR}/deps/lib/lua-5.3.4-${MY_PLATFORM}.lib
        ${LIBWMM}
)
