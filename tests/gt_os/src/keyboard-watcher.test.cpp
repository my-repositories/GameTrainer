#include <memory>

#include <gmock/gmock.h>

#include <gt_os/keyboard-watcher.hpp>

class OsApiMock : public gt::os::OsApi {
  public:
    MOCK_CONST_METHOD1(getAsyncKeyState, SHORT(int));
};

class isKeyDown : public ::testing::Test {
  protected:
    int key{};
    OsApiMock osApiMock;
    gt::os::KeyboardWatcher *keyboardWatcher{};

    void SetUp() override {
        this->key = VK_F6;
        std::vector<int> keysToWatch{this->key};
        this->keyboardWatcher =
            new gt::os::KeyboardWatcher(keysToWatch, &this->osApiMock);

        ON_CALL(this->osApiMock, getAsyncKeyState(::testing::_))
            .WillByDefault(::testing::Return((SHORT)0));
    }

    void TearDown() override { delete this->keyboardWatcher; }
};

TEST_F(isKeyDown, returns_true_when_VK_F6_pressed) {
    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
        .Times(1)
        .WillOnce(::testing::Return((SHORT)-32767));

    bool actual = this->keyboardWatcher->isKeyDown(this->key);

    EXPECT_EQ(true, actual);
}

TEST_F(isKeyDown, returns_false_when_VK_F6_not_pressed) {
    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
        .Times(1)
        .WillOnce(::testing::Return((SHORT)0));

    bool actual = this->keyboardWatcher->isKeyDown(this->key);

    EXPECT_EQ(false, actual);
}
