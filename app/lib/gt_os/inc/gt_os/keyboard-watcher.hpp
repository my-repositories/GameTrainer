#ifndef GAMETRAINER_KEYBOARD_WATCHER_HPP
#define GAMETRAINER_KEYBOARD_WATCHER_HPP

#include <map>
#include <vector>

#include <gt_os/os-api.hpp>

namespace gt::os {
class KeyboardWatcher {
  public:
    explicit KeyboardWatcher(const std::vector<int> &keysToWatch, OsApi* _osApi);

    [[nodiscard]] bool isKeyDown(int key) const;

    [[nodiscard]] bool isKeyPressed(int key);

  private:
    OsApi* osApi;
    std::map<int, bool> states;
};
} // namespace gt::os
#endif // GAMETRAINER_KEYBOARD_WATCHER_HPP
