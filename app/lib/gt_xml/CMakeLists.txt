set(GT_XML_TARGET_NAME gt_xml)
set(GT_XML_DIR ${PROJECT_ROOT_DIR}/app/lib/${GT_XML_TARGET_NAME})

file(GLOB_RECURSE GT_XML_SOURCES ${GT_XML_DIR}/src/*.cpp)
add_library(${GT_XML_TARGET_NAME} ${GT_XML_SOURCES})

target_include_directories(
    ${GT_XML_TARGET_NAME} PUBLIC
    ${PROJECT_ROOT_DIR}/app/lib/gt_os/inc
    ${GT_XML_DIR}/inc
)
