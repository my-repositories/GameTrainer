set(MY_APP_OUTPUT_PATH ${MY_PROJECT_VERSION}-${MY_PLATFORM}-${MY_TOOLCHAIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/bin/${MY_CONFIGURATION}/${MY_APP_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(MY_APP_DIR ${PROJECT_ROOT_DIR}/app)

include(../tools/version/generate_product_version.cmake)
generate_product_version(
        VersionFilesOutputVariable
        NAME ${MY_PROJECT_NAME}
        ICON ${CMAKE_CURRENT_SOURCE_DIR}/logo.ico
        VERSION_FULL ${MY_PROJECT_VERSION}
        FILE_DESCRIPTION "Powered by C++17 & Lua-5.3.4"
)

file(GLOB MY_APP_SOURCES ${MY_APP_DIR}/src/*.cpp)
add_executable(${MY_PROJECT_NAME} ${MY_APP_SOURCES} ${VersionFilesOutputVariable})

target_include_directories(
        ${MY_PROJECT_NAME} PRIVATE
        ${MY_APP_DIR}/inc
)

set_target_properties(
        ${MY_PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_definitions(
        ${MY_PROJECT_NAME} PRIVATE
        MY_PROJECT_VERSION="${MY_PROJECT_VERSION}"
)

if( MY_CONFIGURATION STREQUAL "Debug" )
    target_compile_definitions(
            ${MY_PROJECT_NAME} PRIVATE
            DEBUG=true
    )
endif()


target_link_directories(
        ${MY_PROJECT_NAME} PRIVATE
        ${MY_APP_DIR}/deps/lib
)

include(../tools/find_lib.cmake)
FIND_LIB(LIBWMM "winmm.lib")
message(STATUS "LIBWMM: ${LIBWMM}")

target_link_libraries(
        ${MY_PROJECT_NAME} PRIVATE
        ${MY_LIBRARY_NAME}
        ${MY_APP_DIR}/deps/lib/lua-5.3.4-${MY_PLATFORM}.lib
        ${LIBWMM}
)
