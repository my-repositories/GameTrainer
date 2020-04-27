#include <gt_os/window-manager.hpp>

namespace gt::os {

WindowManager::WindowManager(OsApi* _osApi, WindowFinder* _windowFinder) {
    this->osApi = _osApi;
    this->windowFinder = _windowFinder;
}

void WindowManager::show(const std::string& _title) {
    HWND window = this->windowFinder->findWindow(_title);

    if (window != nullptr) {
        this->osApi->showWindow(window, SW_RESTORE);
        this->osApi->setForegroundWindow(window);
    }
}

bool WindowManager::isOpened(const std::string& _title) {
    HANDLE mutex = this->osApi->createMutex(nullptr, TRUE, _title);

    return mutex == nullptr || this->osApi->getLastError() == ERROR_ALREADY_EXISTS;
}
} // namespace gt::os
