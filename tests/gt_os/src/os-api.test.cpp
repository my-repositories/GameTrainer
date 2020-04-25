#include <gtest/gtest.h>

#include <gt_os/os-api.hpp>

TEST(os_api, getAsyncKeyState) {
gt::os::OsApi api;

EXPECT_EQ(api.getAsyncKeyState(42), 0);
}
