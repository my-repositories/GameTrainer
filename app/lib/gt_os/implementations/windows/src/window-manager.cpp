#include <gt_os/window-manager.hpp>

namespace gt::os
{
    HWND WindowManager::window = nullptr;
    std::string WindowManager::title;

    WindowManager::WindowManager(const std::string& windowTitle)
    {
        WindowManager::title = windowTitle;
    }

    void WindowManager::show()
    {
        ShowWindow(WindowManager::window, SW_RESTORE);
        SetForegroundWindow(WindowManager::window);
    }

    bool WindowManager::isOpened()
    {
        HANDLE mutex = CreateMutex(nullptr, TRUE, WindowManager::title.c_str());

        if (mutex == nullptr || GetLastError() == ERROR_ALREADY_EXISTS)
        {
            if (EnumWindows(&WindowManager::enumWindowsProc, NULL) && window != nullptr)
            {
                return true;
            }
        }

        return false;
    }

    BOOL CALLBACK WindowManager::enumWindowsProc(HWND hwnd, LPARAM) {
        char buffer[255];

        if (GetWindowText(hwnd, buffer, sizeof(buffer))) {
            CharToOem(buffer, buffer);
            if (
                    !strcmp(buffer, WindowManager::title.c_str())
                    || !strcmp(buffer, ("Select " + WindowManager::title).c_str())
                    )
            {
                buffer[0] = '\0';

                if (GetClassName(hwnd, buffer, sizeof(buffer)))
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
