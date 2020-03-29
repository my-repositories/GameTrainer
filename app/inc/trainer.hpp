#ifndef GAMETRAINER_TRAINER_HPP
#define GAMETRAINER_TRAINER_HPP

#include <xstring>
#include <utility>

#include <lua-wrapper.hpp>
#include <window-manager.hpp>
#include <win-utils.hpp>

namespace GameTrainer::app
{
    void loadLuaState(GameTrainer::mylib::LuaWrapper &lua);

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
        GameTrainer::mylib::WindowManager *windowManager;
    };
}

#endif //GAMETRAINER_TRAINER_HPP
