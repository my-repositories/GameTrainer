#ifndef GAMETRAINER_KEYBOARD_WATCHER_FIXTURE_HPP
#define GAMETRAINER_KEYBOARD_WATCHER_FIXTURE_HPP

#include <gmock/gmock.h>

#include <gt_os/keyboard-watcher.hpp>
#include <mocks/os-api.mock.hpp>

class KeyboardWatcherFixture : public ::testing::Test {
protected:
    int key{};
    OsApiMock osApiMock;
    gt::os::KeyboardWatcher *keyboardWatcher{};

    void SetUp() override {
        this->key = VK_F6;
        std::vector<int> keysToWatch{this->key};
        this->keyboardWatcher = new gt::os::KeyboardWatcher(keysToWatch, &this->osApiMock);

        ON_CALL(this->osApiMock, getAsyncKeyState(::testing::_))
            .WillByDefault(::testing::Return((SHORT)0));
    }

    void TearDown() override { delete this->keyboardWatcher; }
};

class isKeyDown : public KeyboardWatcherFixture {};
class isKeyPressed : public KeyboardWatcherFixture {};

#endif // GAMETRAINER_KEYBOARD_WATCHER_FIXTURE_HPP
