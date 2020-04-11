#ifndef GAMETRAINER_WINDOW_MANAGER_HPP
#define GAMETRAINER_WINDOW_MANAGER_HPP

#include <string>
#include <Windows.h>

namespace GameTrainer::mylib::windows
{
    class WindowManager
    {
    public:
        explicit WindowManager(const std::string &title);

        void show();

        [[nodiscard]] bool isOpened();

    private:
        static HWND window;
        static std::string title;

        [[nodiscard]] static  BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
    };
}

#endif //GAMETRAINER_WINDOW_MANAGER_HPP
