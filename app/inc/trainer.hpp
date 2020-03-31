#ifndef GAMETRAINER_TRAINER_HPP
#define GAMETRAINER_TRAINER_HPP

#include <xstring>
#include <utility>

#include <lua/wrapper.hpp>
#include <windows/keyboard-watcher.hpp>
#include <windows/utils.hpp>
#include <windows/window-manager.hpp>

namespace GameTrainer::app
{
    void loadLuaState(GameTrainer::mylib::lua::LuaWrapper &lua);

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
        GameTrainer::mylib::windows::WindowManager *windowManager;
    };
}

#endif //GAMETRAINER_TRAINER_HPP
