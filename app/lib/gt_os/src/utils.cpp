#include <cstring>

#include <gt_os/utils.hpp>
#include <gt_os/os-tlhelp.hpp>

namespace gt::os
{
    void playSound(const char* sound)
    {
        PlaySoundA((LPCSTR)sound, nullptr, SND_APPLICATION | SND_ASYNC | SND_NODEFAULT); // NOLINT(hicpp-signed-bitwise)
    }

    void setConsoleTitle(const char* title)
    {
        SetConsoleTitle(title);
    }

    void sleep(const size_t ms)
    {
        Sleep(ms);
    }

    DWORD_PTR getModuleAddress(const char *moduleName, const DWORD processId)
    {
        MODULEENTRY32 lpModuleEntry = { 0 };
        HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId); // NOLINT(hicpp-signed-bitwise)

        if (!hSnapShot)
            return NULL;
        lpModuleEntry.dwSize = sizeof(lpModuleEntry);
        BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);
        while (bModule)
        {
            if (!strcmp(moduleName, lpModuleEntry.szModule))
            {
                CloseHandle(hSnapShot);
                return (DWORD_PTR)lpModuleEntry.modBaseAddr;
            }
            bModule = Module32Next(hSnapShot, &lpModuleEntry);
        }
        CloseHandle(hSnapShot);
        return NULL;
    }

    DWORD getProcessIdByName(const char* processName)
    {
        DWORD pid = 0;

        // Create toolhelp snapshot
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        PROCESSENTRY32 process;
        ZeroMemory(&process, sizeof(process));
        process.dwSize = sizeof(process);

        // Walkthrough all processes
        if (Process32First(snapshot, &process))
        {
            do
            {
                // Compare process.szExeFile based on format of name, i.e., trim file path
                // trim .exe if necessary, etc
                if (!strcmp(processName, process.szExeFile))
                {
                    pid = process.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &process));
        }

        CloseHandle(snapshot);
        return pid;
    }
}
