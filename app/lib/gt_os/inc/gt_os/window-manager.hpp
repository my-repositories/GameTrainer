#ifndef GAMETRAINER_WINDOW_MANAGER_HPP
#define GAMETRAINER_WINDOW_MANAGER_HPP

#include <string>

#include <gt_os/os-api.hpp>
#include <gt_os/window-finder.hpp>

namespace gt::os {
class WindowManager {
  public:
    explicit WindowManager(OsApi* _osApi, WindowFinder* _windowFinder);

    void show(const std::string& _title);

    [[nodiscard]] bool isOpened(const std::string &_title);

  private:
    OsApi* osApi;
    WindowFinder* windowFinder;
};
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_MANAGER_HPP
