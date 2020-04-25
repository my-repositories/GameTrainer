#include <memory>

#include <gmock/gmock.h>

#include <gt_os/keyboard-watcher.hpp>

class OsApiMock : public gt::os::OsApi {
  public:
    MOCK_METHOD(SHORT, getAsyncKeyState, (int vKey), (const, override));
};

TEST(isKeyDown, returns_true_when_VK_F6_pressed) {
    auto key = VK_F6;
    OsApiMock osApiMock;
    std::vector<int> keysToWatch{key};
    gt::os::KeyboardWatcher keyboardWatcher(keysToWatch, &osApiMock);

    ON_CALL(osApiMock, getAsyncKeyState(::testing::_))
        .WillByDefault(::testing::Return((SHORT)0));

    EXPECT_CALL(osApiMock, getAsyncKeyState(key))
        .Times(1)
        .WillOnce(::testing::Return((SHORT)-32767));

    bool actual = keyboardWatcher.isKeyDown(key);

    EXPECT_EQ(true, actual);
}

TEST(isKeyDown, returns_false_when_VK_F6_not_pressed) {
    auto key = VK_F6;
    OsApiMock osApiMock;
    std::vector<int> keysToWatch{key};
    gt::os::KeyboardWatcher keyboardWatcher(keysToWatch, &osApiMock);

    ON_CALL(osApiMock, getAsyncKeyState(::testing::_))
        .WillByDefault(::testing::Return((SHORT)0));

    EXPECT_CALL(osApiMock, getAsyncKeyState(key))
        .Times(1)
        .WillOnce(::testing::Return((SHORT)0));

    bool actual = keyboardWatcher.isKeyDown(key);

    EXPECT_EQ(false, actual);
}
