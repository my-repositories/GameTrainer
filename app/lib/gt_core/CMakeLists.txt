set(GT_CORE_TARGET_NAME gt_core)
set(GT_CORE_DIR ${PROJECT_ROOT_DIR}/app/lib/${GT_CORE_TARGET_NAME})

file(GLOB_RECURSE GT_CORE_SOURCES ${GT_CORE_DIR}/src/*.cpp)
add_library(${GT_CORE_TARGET_NAME} ${GT_CORE_SOURCES})

target_include_directories(
    ${GT_CORE_TARGET_NAME} PUBLIC
    ${PROJECT_DEPS_DIR}/lua/inc-5.3.4
    ${PROJECT_ROOT_DIR}/app/lib/gt_os/inc
    ${PROJECT_ROOT_DIR}/app/lib/gt_xml/inc
    ${PROJECT_ROOT_DIR}/app/lib/gt_lua/inc
    ${GT_CORE_DIR}/inc
)
