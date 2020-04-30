#include <fixtures/window-finder.fixture.hpp>

TEST_F(WindowFinder__findWindow, should_call_methods_from_windowEnumerator) {
    const std::string title = "TEST_TITLE";
    HWND hwnd = (HWND)1;
    EXPECT_CALL(this->windowEnumeratorMock, setTitle(title))
        .Times(1)
        .WillOnce(::testing::Return(this->windowEnumeratorMock));

    EXPECT_CALL(this->windowEnumeratorMock, enumerate())
        .Times(1)
        .WillOnce(::testing::Return(this->windowEnumeratorMock));

    EXPECT_CALL(this->windowEnumeratorMock, getWindow())
        .Times(1)
        .WillOnce(::testing::Return(hwnd));

    HWND actual = this->windowFinder->findWindow(title);

    EXPECT_EQ(actual, hwnd);
}
