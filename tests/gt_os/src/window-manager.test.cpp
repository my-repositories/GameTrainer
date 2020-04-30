#include <fixtures/window-manager.fixture.hpp>

TEST_F(WindowManager__show, should_not_call_showWindow_and_setForegroundWindow) {
    EXPECT_CALL(this->windowFinderMock, findWindow(this->title))
        .Times(1)
        .WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(this->osApiMock, showWindow(::testing::_, ::testing::_))
        .Times(0);

    EXPECT_CALL(this->osApiMock, setForegroundWindow(::testing::_))
        .Times(0);

    this->windowManager->show(this->title);
}

TEST_F(WindowManager__show, should_call_showWindow_and_setForegroundWindow) {
    HWND hwnd = (HWND)TRUE;
    EXPECT_CALL(this->windowFinderMock, findWindow(this->title))
        .Times(1)
        .WillOnce(::testing::Return(hwnd));

    EXPECT_CALL(this->osApiMock, showWindow(hwnd, SW_RESTORE))
        .Times(1);

    EXPECT_CALL(this->osApiMock, setForegroundWindow(hwnd))
        .Times(1);

    this->windowManager->show(this->title);
}

TEST_F(WindowManager__isOpened, returns_true_if_mutex_is_null) {
    EXPECT_CALL(this->osApiMock, createMutex(nullptr, TRUE, this->title))
        .Times(1)
        .WillOnce(::testing::Return(nullptr));

    bool actual = this->windowManager->isOpened(this->title);

    EXPECT_TRUE(actual);
}

TEST_F(WindowManager__isOpened, returns_false_if_last_error_is_empty) {
    EXPECT_CALL(this->osApiMock, createMutex(nullptr, TRUE, this->title))
        .Times(1)
        .WillOnce(::testing::Return((HANDLE)TRUE));

    EXPECT_CALL(this->osApiMock, getLastError())
        .Times(1)
        .WillOnce(::testing::Return(NULL));

    bool actual = this->windowManager->isOpened(this->title);

    EXPECT_FALSE(actual);
}

TEST_F(WindowManager__isOpened, returns_true_if_last_error_is_not_empty) {
    EXPECT_CALL(this->osApiMock, createMutex(nullptr, TRUE, this->title))
        .Times(1)
        .WillOnce(::testing::Return((HANDLE)TRUE));

    EXPECT_CALL(this->osApiMock, getLastError())
        .Times(1)
        .WillOnce(::testing::Return(ERROR_ALREADY_EXISTS));

    bool actual = this->windowManager->isOpened(this->title);

    EXPECT_TRUE(actual);
}
