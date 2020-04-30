#ifndef GAMETRAINER_WINDOW_ENUMERATOR_MOCK_HPP
#define GAMETRAINER_WINDOW_ENUMERATOR_MOCK_HPP

#include <gt_os/window-enumerator.i.hpp>

class WindowEnumeratorMock : public gt::os::IWindowEnumerator {
public:
    MOCK_METHOD1(setTitle, IWindowEnumerator*(const std::string&));
    MOCK_METHOD0(enumerate, IWindowEnumerator*());
    MOCK_CONST_METHOD0(getWindow, HWND());
};

#endif // GAMETRAINER_WINDOW_ENUMERATOR_MOCK_HPP
//virtual IWindowEnumerator* setTitle(const std::string& _title) = 0;
//virtual IWindowEnumerator* enumerate() = 0;
