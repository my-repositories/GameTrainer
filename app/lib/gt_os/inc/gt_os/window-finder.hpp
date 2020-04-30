#ifndef GAMETRAINER_WINDOW_FINDER_HPP
#define GAMETRAINER_WINDOW_FINDER_HPP

#include <string>

#include <gt_os/window-finder.i.hpp>
#include <gt_os/window-enumerator.i.hpp>

namespace gt::os {
class WindowFinder : public IWindowFinder {
  public:
    explicit WindowFinder(IWindowEnumerator* _windowEnumerator);
    HWND findWindow(const std::string& _title) override;

  private:
    IWindowEnumerator* windowEnumerator;
};
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_FINDER_HPP
