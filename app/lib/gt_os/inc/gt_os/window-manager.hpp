#ifndef GAMETRAINER_WINDOW_MANAGER_HPP
#define GAMETRAINER_WINDOW_MANAGER_HPP

#include <string>

#include <gt_os/os-api.hpp>
#include <gt_os/window-finder.i.hpp>

namespace gt::os {
class WindowManager {
  public:
    explicit WindowManager(OsApi* _osApi, IWindowFinder* _windowFinder);

    void show(const std::string& _title);

    [[nodiscard]] bool isOpened(const std::string &_title);

  private:
    OsApi* osApi;
    IWindowFinder* windowFinder;
};
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_MANAGER_HPP
