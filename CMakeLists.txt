# Download https://cmake.org/download/
cmake_minimum_required(VERSION 3.15)

set(projectName GameTrainer)
project(${projectName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)

set(runtimeOutputDir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/clion)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${runtimeOutputDir}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${runtimeOutputDir}/MinSizeRel)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${runtimeOutputDir}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${runtimeOutputDir}/RelWithDebInfo)

include_directories(inc)


file(GLOB executableFiles
        "inc/*.h"
        "src/*.cpp"
)
add_executable(${projectName} ${executableFiles})

#-DCMAKE_BUILD_TYPE=Release
#-DCMAKE_BUILD_TYPE=Debug
#CMAKE_INCLUDE_PATH
#CMAKE_LIBRARY_PATH