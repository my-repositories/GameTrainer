#ifndef GAMETRAINER_WINDOW_MANAGER_HPP
#define GAMETRAINER_WINDOW_MANAGER_HPP

#include <string>

#include <gt_os/os-api.hpp>

namespace gt::os {
class WindowManager {
  public:
    explicit WindowManager(const std::string &title);

    void show();

    [[nodiscard]] bool isOpened();

  private:
    static OsApi osApi;
    static HWND window;
    static std::string title;

    [[nodiscard]] static BOOL CALLBACK enumWindowsProc(HWND hwnd,
                                                       LPARAM lParam);
};
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_MANAGER_HPP
