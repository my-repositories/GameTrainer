#ifndef GAMETRAINER_UTILS_HPP
#define GAMETRAINER_UTILS_HPP

#include <Windows.h>

namespace GameTrainer::mylib::windows
{
    void playSound(const char* sound);
    void setConsoleTitle(const char* title);
    void sleep(size_t ms);
}

#endif //GAMETRAINER_UTILS_HPP
