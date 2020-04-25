#include <gt_os/keyboard-watcher.hpp>

namespace gt::os {
KeyboardWatcher::KeyboardWatcher(const std::vector<int> &keysToWatch, OsApi* _osApi)
    : osApi(_osApi) {
    for (const auto &key : keysToWatch) {
        this->states[key] = false;
    }
}

bool KeyboardWatcher::isKeyDown(const int key) const {
    return (this->osApi->getAsyncKeyState(key) & 0x8000) > 0; // NOLINT(hicpp-signed-bitwise)
}

bool KeyboardWatcher::isKeyPressed(const int key) {
    auto currentState = this->osApi->getAsyncKeyState(key);

    if ((currentState & 0x8000) && !this->states[key]) // NOLINT(hicpp-signed-bitwise)
    {
        this->states[key] = true;

        return true;
    } else if (!currentState) {
        this->states[key] = false;
    }

    return false;
}
} // namespace gt::os
