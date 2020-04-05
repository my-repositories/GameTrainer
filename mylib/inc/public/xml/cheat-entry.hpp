#ifndef GAMETRAINER_CHEAT_ENTRY_HPP
#define GAMETRAINER_CHEAT_ENTRY_HPP

#include <Windows.h>

namespace GameTrainer::mylib::xml
{
    struct CheatEntry
    {
        short size{};
        short offsetsCount{};
        DWORD offsets[5]{};
        DWORD_PTR address{};
        char module[32];
        char variableType[32];
        char description[56];
    };
}

#endif //GAMETRAINER_CHEAT_ENTRY_HPP
