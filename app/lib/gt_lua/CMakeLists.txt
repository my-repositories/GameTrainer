set(GT_LUA_TARGET_NAME gt_lua)
set(GT_LUA_DIR ${PROJECT_ROOT_DIR}/app/lib/${GT_LUA_TARGET_NAME})

file(GLOB_RECURSE GT_LUA_SOURCES ${GT_LUA_DIR}/src/*.cpp)
add_library(${GT_LUA_TARGET_NAME} ${GT_LUA_SOURCES})

message(STATUS, ${PROJECT_ROOT_DIR}/deps/lua/inc-5.3.4)

target_include_directories(
        ${GT_LUA_TARGET_NAME} PUBLIC
        ${PROJECT_ROOT_DIR}/deps/lua/inc-5.3.4
        ${PROJECT_ROOT_DIR}/app/lib/gt_xml/inc
        ${GT_LUA_DIR}/inc
)
