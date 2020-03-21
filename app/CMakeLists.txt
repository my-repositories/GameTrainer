set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(MY_APP_TARGET ${MY_PROJECT_NAME}-${MY_PROJECT_VERSION}-${MY_PLATFORM}-${MY_TOOLCHAIN})
#set(MY_APP_TARGET ${MY_PROJECT_NAME})

file(GLOB MY_APP_SOURCES "src/*.cpp")
add_executable(${MY_APP_TARGET} ${MY_APP_SOURCES})

target_include_directories(
        ${MY_APP_TARGET} PRIVATE
        inc
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

set(
        LIBWMM_PATHS_TO_FIND
        "C:/Program Files (x86)/Windows Kits/*/Lib/*/*/${MY_PLATFORM}/winmm.lib"
        "C:/Windows Kits/*/Lib/*/*/${MY_PLATFORM}/winmm.lib"
        "C:/Program Files/Windows Kits/*/Lib/*/*/${MY_PLATFORM}/winmm.lib"
)

set(LIBWMM_PATHS "")

foreach(LIBWMM_PATH_TO_FIND ${LIBWMM_PATHS_TO_FIND})
    file(GLOB_RECURSE LIBWMM_PATH_FILES ${LIBWMM_PATH_TO_FIND})
    if (LIBWMM_PATH_FILES)
        foreach(LIBWMM_FILE ${LIBWMM_PATH_FILES})
            get_filename_component(LIBWMM_DIR ${LIBWMM_FILE} DIRECTORY)
            set(LIBWMM_PATHS "${LIBWMM_PATHS};${LIBWMM_DIR}")
        endforeach()
    endif()
endforeach()

FIND_LIBRARY(
        LIBWMM
        NAMES winmm.lib winmm WinMM WinMM.Lib WinMM.lib
        HINTS ${LIBWMM_PATHS}
        PATHS ${LIBWMM_PATHS}
)

message(STATUS "LIBWMM: ${LIBWMM}")

target_link_libraries(
        ${MY_APP_TARGET} PRIVATE
        ${MY_LIBRARY_NAME}
        ${PROJECT_ROOT_DIR}/deps/lib/lua-5.3.4-${MY_PLATFORM}.lib
        ${LIBWMM}
)
