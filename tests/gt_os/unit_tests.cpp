#include <gtest/gtest.h>

//#include <gt_os/os-api.hpp>

TEST(test, empty)
{
//    gt::os::OsApi api;
//
//    int result = api.sum(2, 3);
    int result = 2 + 3;

    EXPECT_EQ(result, 5);
}
