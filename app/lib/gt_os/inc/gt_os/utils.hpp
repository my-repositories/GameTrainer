#ifndef GAMETRAINER_UTILS_HPP
#define GAMETRAINER_UTILS_HPP

#include <gt_os/os-definitions.hpp>

namespace gt::os
{
    void playSound(const char* sound);
    void setConsoleTitle(const char* title);
    void sleep(size_t ms);

    DWORD_PTR getModuleAddress(const char* moduleName, DWORD processId);
    DWORD getProcessIdByName(const char* processName);
}

#endif //GAMETRAINER_UTILS_HPP
