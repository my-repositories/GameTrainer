#ifndef GAMETRAINER_TRAINER_HPP
#define GAMETRAINER_TRAINER_HPP

#include <string>
#include <utility>

#include <game.hpp>
#include <keyboard-watcher.hpp>
#include <utils.hpp>
#include <window-manager.hpp>

namespace gt::core
{
    void loadLuaState(gt::lua::LuaWrapper &lua);

    class Trainer
    {
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
        gt::os::WindowManager *windowManager;
    };
}

#endif //GAMETRAINER_TRAINER_HPP
