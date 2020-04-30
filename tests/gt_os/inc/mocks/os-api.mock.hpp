#ifndef GAMETRAINER_OS_API_MOCK_HPP
#define GAMETRAINER_OS_API_MOCK_HPP

#include <gt_os/os-api.hpp>

class OsApiMock : public gt::os::OsApi {
public:
    MOCK_CONST_METHOD1(getAsyncKeyState, SHORT(int));
    MOCK_CONST_METHOD2(showWindow, BOOL(HWND, int));
    MOCK_CONST_METHOD1(setForegroundWindow, BOOL(HWND));
    MOCK_CONST_METHOD3(createMutex, HANDLE(LPSECURITY_ATTRIBUTES, BOOL, const std::string&));
    MOCK_CONST_METHOD2(enumWindows, BOOL(WNDENUMPROC, LPARAM));
    MOCK_CONST_METHOD0(getLastError, DWORD());
    MOCK_CONST_METHOD3(getWindowText, int(HWND, LPSTR, int));
    MOCK_CONST_METHOD3(getClassName, int(HWND, LPSTR, int));
};

#endif // GAMETRAINER_OS_API_MOCK_HPP
