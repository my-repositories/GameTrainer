#ifndef GAMETRAINER_WINDOW_ENUMERATOR_FIXTURE_HPP
#define GAMETRAINER_WINDOW_ENUMERATOR_FIXTURE_HPP

#include <gmock/gmock.h>

#include <gt_os/window-enumerator.hpp>
#include <mocks/os-api.mock.hpp>

class WindowEnumeratorFixture : public ::testing::Test {
protected:
    std::string title{};
    OsApiMock osApiMock;
    gt::os::WindowEnumerator *windowEnumerator{};

    void SetUp() override {
        this->title = "TEST_TITLE";
        this->windowEnumerator = new gt::os::WindowEnumerator(&this->osApiMock);
    }

    void TearDown() override {
        delete this->windowEnumerator;
    }
};

class WindowEnumerator__enumerate : public WindowEnumeratorFixture {};

#endif // GAMETRAINER_WINDOW_ENUMERATOR_FIXTURE_HPP
