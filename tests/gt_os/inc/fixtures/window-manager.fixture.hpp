#ifndef GAMETRAINER_WINDOW_MANAGER_FIXTURE_HPP
#define GAMETRAINER_WINDOW_MANAGER_FIXTURE_HPP

#include <gmock/gmock.h>

#include <gt_os/window-manager.hpp>
#include <mocks/os-api.mock.hpp>
#include <mocks/window-finder.mock.hpp>

class WindowManagerFixture : public ::testing::Test {
protected:
    std::string title{};
    OsApiMock osApiMock;
    WindowFinderMock windowFinderMock;
    gt::os::WindowManager *windowManager{};

    void SetUp() override {
        this->title = "TEST_TITLE";
        this->windowManager = new gt::os::WindowManager(&this->osApiMock, &this->windowFinderMock);
    }

    void TearDown() override {
        delete this->windowManager;
    }
};

class WindowManager__show : public WindowManagerFixture {};
class WindowManager__isOpened : public WindowManagerFixture {};

#endif // GAMETRAINER_WINDOW_MANAGER_FIXTURE_HPP
