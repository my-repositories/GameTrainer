#include <cstring>

#include <gt_os/window-enumerator.hpp>

namespace gt::os {
OsApi* WindowEnumerator::osApi = nullptr;
HWND WindowEnumerator::window = nullptr;
std::string WindowEnumerator::title;

WindowEnumerator::WindowEnumerator(OsApi *_osApi) {
    WindowEnumerator::osApi = _osApi;
}

WindowEnumerator* WindowEnumerator::setTitle(const std::string &_title) {
    WindowEnumerator::title = _title;

    return this;
}

WindowEnumerator* WindowEnumerator::enumerate() {
    WindowEnumerator::osApi->enumWindows(&WindowEnumerator::enumWindowsProc, NULL);

    return this;
}

HWND WindowEnumerator::getWindow() const {
    return WindowEnumerator::window;
}

BOOL CALLBACK WindowEnumerator::enumWindowsProc(HWND hwnd, LPARAM) {
    char buffer[255];

    if (WindowEnumerator::osApi->getWindowText(hwnd, buffer, sizeof(buffer))) {
        WindowEnumerator::osApi->charToOem(buffer, buffer);

        if (!strcmp(buffer, WindowEnumerator::title.c_str()) ||
            !strcmp(buffer, ("Select " + WindowEnumerator::title).c_str())) {
            buffer[0] = '\0';

            if (WindowEnumerator::osApi->getClassName(hwnd, buffer, sizeof(buffer))) {
                if (!strcmp("ConsoleWindowClass", buffer)) {
                    WindowEnumerator::window = hwnd;

                    return FALSE;
                }
            }
        }
    }

    buffer[0] = '\0';

    return TRUE;
}
} // namespace gt::os
