# Download https://cmake.org/download/
cmake_minimum_required(VERSION 3.15)

if (NOT DEFINED MY_PROJECT_NAME)
    set(MY_PROJECT_NAME GameTrainer)
endif()

if (NOT DEFINED MY_PROJECT_VERSION)
    set(MY_PROJECT_VERSION 0.0.1)
endif()

if (NOT DEFINED MY_CONFIGURATION)
    set(MY_CONFIGURATION Release)
endif()

if (NOT DEFINED MY_PLATFORM)
    set(MY_PLATFORM x86)
endif()

project(${MY_PROJECT_NAME} VERSION ${MY_PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:LIBCMT /NODEFAULTLIB:MSVCRT")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CONFIGURATION_TYPES ${MY_CONFIGURATION} CACHE STRING "" FORCE)

set(MY_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${MY_OUTPUT_DIR}/Release-${MY_PLATFORM})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${MY_OUTPUT_DIR}/Debug-${MY_PLATFORM})

file(GLOB MY_EXECUTABLE_FILES src/*.cpp)
add_executable(${MY_PROJECT_NAME} ${MY_EXECUTABLE_FILES})

set_target_properties(
        ${MY_PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)

target_compile_definitions(
        ${MY_PROJECT_NAME} PRIVATE
        MY_VERSION="${MY_PROJECT_VERSION}"
)

target_include_directories(
        ${MY_PROJECT_NAME} PRIVATE
        inc
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/inc/lua-5.3.4
)

target_link_directories(
        ${MY_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib
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
        ${MY_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/lib/lua-5.3.4-${MY_PLATFORM}.lib
        ${LIBWMM}
)
