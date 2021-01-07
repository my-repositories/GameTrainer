#include <fixtures/window-enumerator.fixture.hpp>

TEST_F(WindowEnumerator__enumerate, should_call_enumWindows_from_osApi) {
    EXPECT_CALL(this->osApiMock, enumWindows(::testing::_, NULL))
        .Times(1);

    this->windowEnumerator->enumerate();
}
