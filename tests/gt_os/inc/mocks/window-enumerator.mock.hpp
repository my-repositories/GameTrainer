#ifndef GAMETRAINER_WINDOW_ENUMERATOR_MOCK_HPP
#define GAMETRAINER_WINDOW_ENUMERATOR_MOCK_HPP

#include <gt_os/window-enumerator.i.hpp>

class WindowEnumeratorMock : public gt::os::IWindowEnumerator {
public:
    MOCK_METHOD1(setTitle, gt::os::IWindowEnumerator*(const std::string&));
    MOCK_METHOD0(enumerate, gt::os::IWindowEnumerator*());
    MOCK_CONST_METHOD0(getWindow, HWND());
};

#endif // GAMETRAINER_WINDOW_ENUMERATOR_MOCK_HPP
