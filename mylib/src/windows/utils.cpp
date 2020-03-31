#include <windows/utils.hpp>

namespace GameTrainer::mylib::windows
{
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
