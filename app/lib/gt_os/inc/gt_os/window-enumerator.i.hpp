#ifndef GAMETRAINER_WINDOW_ENUMERATOR_I_HPP
#define GAMETRAINER_WINDOW_ENUMERATOR_I_HPP

#include <string>

#include <gt_os/os-definitions.hpp>

namespace gt::os {
    class IWindowEnumerator {
    public:
        virtual IWindowEnumerator* setTitle(const std::string& _title) = 0;
        virtual IWindowEnumerator* enumerate() = 0;
        [[nodiscard]] virtual HWND getWindow() const = 0;
    };
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_ENUMERATOR_HPP
