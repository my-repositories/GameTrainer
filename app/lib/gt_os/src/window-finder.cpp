#include <gt_os/window-finder.hpp>

namespace gt::os {

WindowFinder::WindowFinder(IWindowEnumerator *_windowEnumerator) {
    this->windowEnumerator = _windowEnumerator;
}

HWND WindowFinder::findWindow(const std::string &_title) {
    return this->windowEnumerator
        ->setTitle(_title)
        ->enumerate()
        ->getWindow();
}
} // namespace gt::os
