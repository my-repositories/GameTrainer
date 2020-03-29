#ifndef GAMETRAINER_WINDOW_MANAGER_HPP
#define GAMETRAINER_WINDOW_MANAGER_HPP

#include <xstring>
#include <Windows.h>

namespace GameTrainer::mylib {
    class WindowManager {
    public:
        explicit WindowManager(const std::string &title);

        void show();

        bool isOpened();

    private:
        static HWND window;
        static std::string title;

        static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
    };
}

#endif //GAMETRAINER_WINDOW_MANAGER_HPP
