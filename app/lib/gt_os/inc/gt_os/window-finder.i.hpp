#ifndef GAMETRAINER_WINDOW_FINDER_I_HPP
#define GAMETRAINER_WINDOW_FINDER_I_HPP

#include <string>

#include <gt_os/os-definitions.hpp>

namespace gt::os {
    class IWindowFinder {
    public:
        virtual HWND findWindow(const std::string& _title) = 0;
    };
} // namespace gt::os

#endif // GAMETRAINER_WINDOW_FINDER_I_HPP
