#ifndef GAMETRAINER_GAME_HPP
#define GAMETRAINER_GAME_HPP

#include <gt_lua/wrapper.hpp>
#include <gt_os/os-api.hpp>
#include <gt_os/utils.hpp>

namespace gt::core
{
    class Game {
    public:
        explicit Game(DWORD processId);
        ~Game();

        void updateValue(const gt::xml::CheatEntry* entry, float valueToAdd);

    private:
        os::OsApi osApi;
        DWORD processId;
        HANDLE process;

        // TODO: move from here to smth.
        [[nodiscard]] DWORD_PTR getValueAddress(const gt::xml::CheatEntry* entry) const;

        // TODO: move from here to smth.
        [[nodiscard]] BOOL isWow64() const;
    };
}

#endif //GAMETRAINER_GAME_HPP
