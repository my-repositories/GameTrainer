set(GT_OS_TARGET_NAME gt_os)
set(GT_OS_DIR ${PROJECT_ROOT_DIR}/app/lib/${GT_OS_TARGET_NAME}/implementations/windows)

file(GLOB_RECURSE GT_OS_SOURCES ${GT_OS_DIR}/src/*.cpp)
add_library(${GT_OS_TARGET_NAME} ${GT_OS_SOURCES})

target_include_directories(
        ${GT_OS_TARGET_NAME} PUBLIC
        ${GT_OS_DIR}/inc
)
