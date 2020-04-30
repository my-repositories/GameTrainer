#ifndef GAMETRAINER_WINDOW_ENUMERATOR_HPP
#define GAMETRAINER_WINDOW_ENUMERATOR_HPP

#include <string>

#include <gt_os/os-api.hpp>
#include <gt_os/window-enumerator.i.hpp>

namespace gt::os {
    class WindowEnumerator : public IWindowEnumerator {
    public:
        explicit WindowEnumerator(OsApi* _osApi);

        IWindowEnumerator* setTitle(const std::string& _title) override;
        IWindowEnumerator* enumerate() override;
        [[nodiscard]] HWND getWindow() const override;

    private:
        static OsApi* osApi;
        static HWND window;
        static std::string title;

        [[nodiscard]] static BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam);
    };
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_ENUMERATOR_HPP
