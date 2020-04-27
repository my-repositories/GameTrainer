#ifndef GAMETRAINER_WINDOW_ENUMERATOR_HPP
#define GAMETRAINER_WINDOW_ENUMERATOR_HPP

#include <string>

#include <gt_os/os-api.hpp>

namespace gt::os {
    class WindowEnumerator {
    public:
        explicit WindowEnumerator(OsApi* _osApi);

        WindowEnumerator* setTitle(const std::string& _title);
        WindowEnumerator* enumerate();
        [[nodiscard]] HWND getWindow() const;

    private:
        static OsApi* osApi;
        static HWND window;
        static std::string title;

        [[nodiscard]] static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
    };
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_ENUMERATOR_HPP
