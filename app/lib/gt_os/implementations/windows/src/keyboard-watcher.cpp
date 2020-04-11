#include <keyboard-watcher.hpp>

namespace GameTrainer::mylib::windows
{
    KeyboardWatcher::KeyboardWatcher(const std::vector<int> &keysToWatch)
    {
        for (const auto& key : keysToWatch)
        {
            this->states[key] = false;
        }
    }

    bool KeyboardWatcher::isKeyDown(const int key) const
    {
        return (GetAsyncKeyState(key) & 0x8000) > 0; // NOLINT(hicpp-signed-bitwise)
    }

    bool KeyboardWatcher::isKeyPressed(const int key)
    {
        auto currentState = GetAsyncKeyState(key);

        if ((currentState & 0x8000) && !this->states[key]) // NOLINT(hicpp-signed-bitwise)
        {
            this->states[key] = true;

            return true;
        }
        else if (!currentState)
        {
            this->states[key] = false;
        }

        return false;
    }
}
