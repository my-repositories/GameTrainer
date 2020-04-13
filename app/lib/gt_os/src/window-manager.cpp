#include <gt_os/window-manager.hpp>

namespace gt::os
{
    OsApi WindowManager::osApi;
    HWND WindowManager::window = nullptr;
    std::string WindowManager::title;

    WindowManager::WindowManager(const std::string& windowTitle)
    {
        WindowManager::title = windowTitle;
    }

    void WindowManager::show()
    {
        WindowManager::osApi.showWindow(WindowManager::window, SW_RESTORE);
        WindowManager::osApi.setForegroundWindow(WindowManager::window);
    }

    bool WindowManager::isOpened()
    {
        HANDLE mutex = WindowManager::osApi.createMutex(nullptr, TRUE, WindowManager::title.c_str());

        if (mutex == nullptr || WindowManager::osApi.getLastError() == ERROR_ALREADY_EXISTS)
        {
            if (WindowManager::osApi.enumWindows(&WindowManager::enumWindowsProc, NULL) && window != nullptr)
            {
                return true;
            }
        }

        return false;
    }

    BOOL CALLBACK WindowManager::enumWindowsProc(HWND hwnd, LPARAM) {
        char buffer[255];

        if (WindowManager::osApi.getWindowText(hwnd, buffer, sizeof(buffer))) {
            WindowManager::osApi.charToOem(buffer, buffer);
            if (
                    !strcmp(buffer, WindowManager::title.c_str())
                    || !strcmp(buffer, ("Select " + WindowManager::title).c_str())
                    )
            {
                buffer[0] = '\0';

                if (WindowManager::osApi.getClassName(hwnd, buffer, sizeof(buffer)))
                {
                    if (!strcmp("ConsoleWindowClass", buffer))
                    {
                        WindowManager::window = hwnd;
                    }
                }
            }
        }

        buffer[0] = '\0';

        return TRUE;
    }
}
