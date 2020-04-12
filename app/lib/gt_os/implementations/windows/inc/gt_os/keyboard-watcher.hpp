#ifndef GAMETRAINER_KEYBOARD_WATCHER_HPP
#define GAMETRAINER_KEYBOARD_WATCHER_HPP

#include <map>
#include <vector>
#include <Windows.h>

namespace gt::os
{
    class KeyboardWatcher
    {
    public:
        explicit KeyboardWatcher(const std::vector<int>& keysToWatch);

        [[nodiscard]] bool isKeyDown(int key) const;

        [[nodiscard]] bool isKeyPressed(int key);

    private:
        std::map<int, bool> states;
    };
}
#endif //GAMETRAINER_KEYBOARD_WATCHER_HPP
