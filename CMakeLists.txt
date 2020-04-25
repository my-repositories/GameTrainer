# Download https://cmake.org/download/
cmake_minimum_required(VERSION 3.15)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_DEPS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT DEFINED GT_PROJECT_NAME)
    set(GT_PROJECT_NAME GameTrainer)
endif()

if (NOT DEFINED GT_PROJECT_VERSION)
    set(GT_PROJECT_VERSION 0.0.1)
endif()

if (NOT DEFINED GT_CONFIGURATION)
    set(GT_CONFIGURATION Debug)
endif()

if (NOT DEFINED GT_PLATFORM)
    set(GT_PLATFORM x86)
endif()

if (NOT DEFINED GT_TOOLCHAIN)
    set(GT_TOOLCHAIN msvc15)
endif()

set(CMAKE_CONFIGURATION_TYPES ${GT_CONFIGURATION} CACHE STRING "" FORCE)

set(CMAKE_CXX_STANDARD 17)
#set_target_properties(
#        ${TARGET} PROPERTIES
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED YES
#        CXX_EXTENSIONS NO
#)


if(GT_CONFIGURATION STREQUAL "Debug" AND GT_OS STREQUAL "win")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
endif()

project(${GT_PROJECT_NAME} VERSION ${GT_PROJECT_VERSION})

add_subdirectory(app)

if(GT_ENABLE_TESTING)
    message(STATUS, ${GT_ENABLE_TESTING})
    enable_testing()
    add_subdirectory(${PROJECT_DEPS_DIR}/googletest)
    add_subdirectory(tests)
endif()
