set(GT_TEST_TARGET_NAME test_gt_xml)

include(${PROJECT_ROOT_DIR}/tools/testing/init.cmake)
include(${PROJECT_ROOT_DIR}/tools/testing/configure.cmake)

INIT_TEST(${GT_TEST_TARGET_NAME})
CONFIGURE_TEST(${GT_TEST_TARGET_NAME})

target_link_libraries(
        ${GT_TEST_TARGET_NAME} PRIVATE
        gt_xml
        gt_os
)

target_include_directories(
        ${GT_TEST_TARGET_NAME} PRIVATE
        ${PROJECT_ROOT_DIR}/app/lib/gt_xml/inc
        ${PROJECT_ROOT_DIR}/app/lib/gt_os/inc
)


