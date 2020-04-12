#ifndef GAMETRAINER_GAME_HPP
#define GAMETRAINER_GAME_HPP

#include <Windows.h>

#include <gt_lua/wrapper.hpp>
#include <gt_os/utils.hpp>

namespace gt::core
{
    class Game {
    public:
        explicit Game(DWORD processId);
        ~Game();

        void updateValue(const gt::xml::CheatEntry* entry, float valueToAdd);

    private:
        DWORD processId;
        HANDLE process;

        [[nodiscard]] DWORD_PTR getValueAddress(const gt::xml::CheatEntry* entry) const;

        [[nodiscard]] BOOL isWow64() const;
    };
}

#endif //GAMETRAINER_GAME_HPP
