#ifndef GAMETRAINER_GAME_HPP
#define GAMETRAINER_GAME_HPP

#include <Windows.h>

#include <lua/wrapper.hpp>
#include <windows/utils.hpp>

namespace GameTrainer::app
{
    class Game {
    public:
        explicit Game(DWORD processId);
        ~Game();

        void updateValue(const GameTrainer::mylib::xml::CheatEntry* entry, float valueToAdd);

    private:
        DWORD processId;
        HANDLE process;

        [[nodiscard]] DWORD_PTR getValueAddress(const GameTrainer::mylib::xml::CheatEntry* entry) const;

        [[nodiscard]] BOOL isWow64() const;
    };
}

#endif //GAMETRAINER_GAME_HPP
