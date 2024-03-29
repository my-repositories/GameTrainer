#ifndef GAMETRAINER_WINDOW_FINDER_FIXTURE_HPP
#define GAMETRAINER_WINDOW_FINDER_FIXTURE_HPP

#include <gmock/gmock.h>

#include <gt_os/window-finder.hpp>
#include <mocks/window-enumerator.mock.hpp>

class WindowFinderFixture : public ::testing::Test {
protected:
    WindowEnumeratorMock windowEnumeratorMock;
    gt::os::WindowFinder *windowFinder{};

    void SetUp() override {
        this->windowFinder = new gt::os::WindowFinder(&this->windowEnumeratorMock);
    }

    void TearDown() override {
        delete this->windowFinder;
    }
};

class WindowFinder__findWindow : public WindowFinderFixture {};

#endif // GAMETRAINER_WINDOW_FINDER_FIXTURE_HPP
