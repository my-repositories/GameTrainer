#ifndef GAMETRAINER_WINDOW_FINDER_MOCK_HPP
#define GAMETRAINER_WINDOW_FINDER_MOCK_HPP

#include <gt_os/window-finder.i.hpp>

class WindowFinderMock : public gt::os::IWindowFinder {
public:
    MOCK_METHOD1(findWindow, HWND(const std::string&));
};

#endif // GAMETRAINER_WINDOW_FINDER_MOCK_HPP
