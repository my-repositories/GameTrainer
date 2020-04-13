set(GT_APP_OUTPUT_PATH ${GT_PROJECT_VERSION}-${GT_PLATFORM}-${GT_TOOLCHAIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/bin/${GT_CONFIGURATION}/${GT_APP_OUTPUT_PATH})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(GT_APP_DIR ${PROJECT_ROOT_DIR}/app)

include(${PROJECT_ROOT_DIR}/tools/version/generate_product_version.cmake)
generate_product_version(
        VersionFilesOutputVariable
        NAME ${GT_PROJECT_NAME}
        ICON ${GT_APP_DIR}/resources/logo.ico
        VERSION_FULL ${GT_PROJECT_VERSION}
        FILE_DESCRIPTION "Powered by C++17 & Lua-5.3.4"
)

file(GLOB GT_APP_SOURCES ${GT_APP_DIR}/executable/console/src/*.cpp)
add_executable(${GT_PROJECT_NAME} ${GT_APP_SOURCES} ${VersionFilesOutputVariable})

set_target_properties(
        ${GT_PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_definitions(
        ${GT_PROJECT_NAME} PRIVATE
        GT_PROJECT_VERSION="${GT_PROJECT_VERSION}"
        GT_PROJECT_NAME="${GT_PROJECT_NAME}"
)

if(GT_CONFIGURATION STREQUAL "Debug")
    target_compile_definitions(
            ${GT_PROJECT_NAME} PRIVATE
            DEBUG=true
    )
endif()

target_include_directories(
        ${GT_PROJECT_NAME} PRIVATE
        ${PROJECT_ROOT_DIR}/app/lib/gt_os/inc
        ${PROJECT_ROOT_DIR}/app/lib/gt_xml/inc
        ${PROJECT_ROOT_DIR}/app/lib/gt_lua/inc
        ${PROJECT_ROOT_DIR}/app/lib/gt_core/inc
)

include(${PROJECT_ROOT_DIR}/tools/find_lib.cmake)
FIND_LIB(LIBWMM "winmm.lib")
message(STATUS "LIBWMM: ${LIBWMM}")

if(GT_OS STREQUAL "win")
set(GT_LIB_SUFFIX lib)
elseif(APPLE)
set(GT_LIB_SUFFIX a)
else()
set(GT_LIB_SUFFIX so)
endif()

target_link_libraries(
        ${GT_PROJECT_NAME} PRIVATE
        ${PROJECT_ROOT_DIR}/deps/lua/lua-5.3.4-${GT_PLATFORM}.${GT_LIB_SUFFIX}
        gt_os
        gt_xml
        gt_lua
        gt_core
)

if(LIBWMM)
    target_link_libraries(
            ${GT_PROJECT_NAME} PRIVATE
            ${LIBWMM}
    )
endif()


