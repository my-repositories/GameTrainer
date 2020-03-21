https://habr.com/ru/post/343622/

https://ru.wikipedia.org/wiki/%D0%9F%D0%BE%D0%BB%D1%83%D1%87%D0%B5%D0%BD%D0%B8%D0%B5_%D1%80%D0%B5%D1%81%D1%83%D1%80%D1%81%D0%B0_%D0%B5%D1%81%D1%82%D1%8C_%D0%B8%D0%BD%D0%B8%D1%86%D0%B8%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F
https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs
http://open-std.org/JTC1/SC22/WG21/docs/papers/2018/p1204r0.html
https://stackoverflow.com/questions/19877065/cmake-d-vartype-value-what-does-the-parameter-d-mean
https://habr.com/ru/post/329264/


remove clion/msvs in bin

editorconfig

deps/include -> deps/inc


set(CMAKE_BUILD_TYPE Release)
cmake -B_build DCMAKE_BUILD_TYPE=Release


lua-5.3.5_Win64_vc15_lib.zip
lua-5.3.5_Win32_vc15_lib.zip



Makefile
cmake: clean lib_clean app_clean cmake_compile cmake_link
cmake_compile:
	cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake_link:
	cmake --build build --config Release






app
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(GLOB APP_SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME} testlib)
target_include_directories(${PROJECT_NAME} PRIVATE inc ${PROJECT_ROOT_DIR}/deps/inc)
(edited)



lib
set(LIBRARY_NAME testlib)
file(GLOB LIBRARY_SOURCES "src/*.cpp")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_ROOT_DIR}/deps/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
add_library(${LIBRARY_NAME} ${LIBRARY_SOURCES})
target_include_directories(${LIBRARY_NAME} PRIVATE inc)
(edited)



root
cmake_minimum_required(VERSION 3.16)
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_NAME libqa)
set(CMAKE_CONFIGURATION_TYPES "Release" CACHE STRING "" FORCE)
set(CMAKE_BUILD_TYPE Release)
project(${PROJECT_NAME})
add_subdirectory(lib)
add_subdirectory(app)







