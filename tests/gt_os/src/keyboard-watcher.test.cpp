#include <fixtures/keyboard-watcher.fixture.hpp>

const SHORT KEY_DOWN_STATE = (SHORT)-32767;
const SHORT KEY_UP_STATE = (SHORT)0;

TEST_F(isKeyDown, returns_true_when_VK_F6_pressed) {
    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
        .Times(1)
        .WillOnce(::testing::Return(KEY_DOWN_STATE));

    bool actual = this->keyboardWatcher->isKeyDown(this->key);

    EXPECT_EQ(true, actual);
}

TEST_F(isKeyDown, returns_false_when_VK_F6_not_pressed) {
    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
        .Times(1)
        .WillOnce(::testing::Return(KEY_UP_STATE));

    bool actual = this->keyboardWatcher->isKeyDown(this->key);

    EXPECT_EQ(false, actual);
}

TEST_F(isKeyPressed, returns_false_by_default) {
    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
        .Times(1)
        .WillOnce(::testing::Return(KEY_UP_STATE));

    bool actual = this->keyboardWatcher->isKeyPressed(this->key);

    EXPECT_EQ(false, actual);
}

TEST_F(isKeyPressed, returns_true_once) {
    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
        .Times(1)
        .WillOnce(::testing::Return(KEY_DOWN_STATE));

    bool actual = this->keyboardWatcher->isKeyPressed(this->key);

    EXPECT_EQ(true, actual);
}

TEST_F(isKeyPressed, returns_always_false_after_first_true) {
    const int checksCount = 5;

    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
        .Times(checksCount)
        .WillOnce(::testing::Return(KEY_DOWN_STATE))
        .WillRepeatedly(::testing::Return(KEY_UP_STATE));

    (void)this->keyboardWatcher->isKeyPressed(this->key);

    for (int i = 1; i < checksCount; ++i) {
        bool actual = this->keyboardWatcher->isKeyPressed(this->key);

        EXPECT_EQ(false, actual);
    }
}

TEST_F(isKeyPressed, returns_true_after_keyup) {
    EXPECT_CALL(this->osApiMock, getAsyncKeyState(this->key))
            .Times(3)
            .WillOnce(::testing::Return(KEY_DOWN_STATE))
            .WillOnce(::testing::Return(KEY_UP_STATE))
            .WillOnce(::testing::Return(KEY_DOWN_STATE));

    (void)this->keyboardWatcher->isKeyPressed(this->key);
    (void)this->keyboardWatcher->isKeyPressed(this->key);
    bool actual = this->keyboardWatcher->isKeyPressed(this->key);

    EXPECT_EQ(true, actual);
}
