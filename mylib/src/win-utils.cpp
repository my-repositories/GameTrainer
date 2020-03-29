#include <win-utils.hpp>

namespace GameTrainer::mylib::win
{
    bool ifKeyPressed(const int key)
    {
        return GetAsyncKeyState(key) & 1; // NOLINT(hicpp-signed-bitwise)
    }

    void playSound(const char* sound)
    {
        PlaySoundA((LPCSTR)sound, nullptr, SND_APPLICATION | SND_ASYNC | SND_NODEFAULT); // NOLINT(hicpp-signed-bitwise)
    }

    void setConsoleTitle(const char* title)
    {
        SetConsoleTitle(title);
    }

    void sleep(const size_t ms)
    {
        Sleep(ms);
    }
}
