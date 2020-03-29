#ifndef GAMETRAINER_WIN_UTILS_HPP
#define GAMETRAINER_WIN_UTILS_HPP

#include <Windows.h>

namespace GameTrainer::mylib::win
{
    bool ifKeyPressed(int key);
    void playSound(const char* sound);
    void setConsoleTitle(const char* title);
    void sleep(size_t ms);
}

#endif //GAMETRAINER_WIN_UTILS_HPP
