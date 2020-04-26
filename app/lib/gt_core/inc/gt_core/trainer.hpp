#ifndef GAMETRAINER_TRAINER_HPP
#define GAMETRAINER_TRAINER_HPP

#include <string>
#include <utility>

#include <gt_core/game.hpp>
#include <gt_os/keyboard-watcher.hpp>
#include <gt_os/utils.hpp>
#include <gt_os/window-manager.hpp>

namespace gt::core {
void loadLuaState(gt::lua::LuaWrapper &lua);

class Trainer {
  public:
    explicit Trainer(std::string trainerTitle);

    ~Trainer();

    [[nodiscard]] bool trainerIsRunning() const;

    void showOpenedWindow() const;

    [[nodiscard]] bool chooseConfig() const;

    [[nodiscard]] bool gameIsRunning() const;

    void start() const;

  private:
    const std::string title;
    gt::os::OsApi *osApi;
    gt::os::WindowManager *windowManager;
};
} // namespace gt::core

#endif // GAMETRAINER_TRAINER_HPP
