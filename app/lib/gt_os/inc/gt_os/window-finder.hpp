#ifndef GAMETRAINER_WINDOW_FINDER_HPP
#define GAMETRAINER_WINDOW_FINDER_HPP

#include <string>

#include <gt_os/window-enumerator.hpp>

namespace gt::os {
class WindowFinder {
  public:
    explicit WindowFinder(WindowEnumerator* _windowEnumerator);
    HWND findWindow(const std::string& _title);

  private:
    WindowEnumerator* windowEnumerator;
};
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_FINDER_HPP
