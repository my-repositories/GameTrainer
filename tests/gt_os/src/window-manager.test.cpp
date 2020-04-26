#include <cstring>

#include <fixtures/window-manager.fixture.hpp>

TEST_F(show, should_call_showWindow_and_setForegroundWindow) {
    EXPECT_CALL(this->osApiMock, showWindow(::testing::_, SW_RESTORE))
        .Times(1);

    EXPECT_CALL(this->osApiMock, setForegroundWindow(::testing::_))
        .Times(1);

    this->windowManager->show();
}

TEST_F(isOpened, returns_false_if_mutex_is_null) {
    EXPECT_CALL(this->osApiMock,
                createMutex(nullptr, TRUE, this->title))
        .Times(1)
        .WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(this->osApiMock, enumWindows(::testing::_, NULL))
        .Times(1)
        .WillOnce(::testing::DoDefault());

    bool actual = this->windowManager->isOpened();

    EXPECT_FALSE(actual);
}

TEST_F(isOpened, returns_true) {
    EXPECT_CALL(this->osApiMock,
                createMutex(nullptr, TRUE, this->title))
        .Times(1)
        .WillOnce(::testing::DoDefault());

    EXPECT_CALL(this->osApiMock,
                getLastError())
        .Times(1)
        .WillOnce(::testing::DoDefault());

    EXPECT_CALL(this->osApiMock,
                getWindowText(::testing::_, ::testing::_, ::testing::_))
        .Times(1)
        .WillOnce(::testing::DoDefault());

    EXPECT_CALL(this->osApiMock,
                getClassName(::testing::_, ::testing::_, ::testing::_))
        .Times(1)
        .WillOnce(::testing::DoDefault());

    EXPECT_CALL(this->osApiMock, enumWindows(::testing::_, NULL))
        .Times(1)
        .WillOnce(::testing::DoAll(
            ::testing::Invoke([](WNDENUMPROC lpEnumFunc, LPARAM lParam) -> BOOL {
               return lpEnumFunc((HWND)TRUE, lParam);
           }),
           ::testing::Return(TRUE))
        );

    bool actual = this->windowManager->isOpened();

    EXPECT_TRUE(actual);
}

/*
bool WindowManager::isOpened() {
    HANDLE mutex = WindowManager::osApi.createMutex(
        nullptr, TRUE, WindowManager::title.c_str());

    if (mutex == nullptr ||
        WindowManager::osApi.getLastError() == ERROR_ALREADY_EXISTS) {
        if (WindowManager::osApi.enumWindows(&WindowManager::enumWindowsProc,
                                             NULL) &&
            window != nullptr) {
            return true;
        }
    }

    return false;
}
 * */
