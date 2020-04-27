#ifndef GAMETRAINER_WINDOW_MANAGER_FIXTURE_HPP
#define GAMETRAINER_WINDOW_MANAGER_FIXTURE_HPP

#include <gmock/gmock.h>

#include <gt_os/window-manager.hpp>
#include <mocks/os-api.mock.hpp>

class WindowManagerFixture : public ::testing::Test {
protected:
    std::string title{};
    OsApiMock osApiMock;
    gt::os::WindowManager *windowManager{};

    void SetUp() override {
        this->title = "TEST_TITLE";
        this->windowManager = new gt::os::WindowManager(this->title, &this->osApiMock);

        ON_CALL(this->osApiMock, createMutex(::testing::_, ::testing::_, ::testing::_))
            .WillByDefault(::testing::Return((void *)TRUE));

        ON_CALL(this->osApiMock, enumWindows(::testing::_, NULL))
            .WillByDefault(::testing::Return(NULL));

        ON_CALL(this->osApiMock, getLastError())
            .WillByDefault(::testing::Return(ERROR_ALREADY_EXISTS));

        ON_CALL(this->osApiMock,
                getWindowText(::testing::_, ::testing::_, ::testing::_))
            .WillByDefault(
                ::testing::DoAll(
                    ::testing::Invoke([](HWND, LPSTR dest, int) -> int {
                        auto source = (char *)"TEST_TITLE";
#ifdef OS_WINDOWS
                        strcpy_s(dest, strlen(source) + 1, source);
#else
                        strcpy(dest, source);
#endif
                        return 1;
                    }),
                    ::testing::Return(1))
            );

        ON_CALL(this->osApiMock,
                getClassName(::testing::_, ::testing::_, ::testing::_))
            .WillByDefault(
                ::testing::DoAll(
                    ::testing::Invoke([](HWND, LPSTR dest, int) -> int {
                        auto source = (char *)"ConsoleWindowClass";
#ifdef OS_WINDOWS
                        strcpy_s(dest, strlen(source) + 1, source);
#else
                        strcpy(dest, source);
#endif
                        return 1;
                    }),
                    ::testing::Return(1))
            );
    }

    void TearDown() override { delete this->windowManager; }
};

class show : public WindowManagerFixture {};
class isOpened : public WindowManagerFixture {};

#endif // GAMETRAINER_WINDOW_MANAGER_FIXTURE_HPP
