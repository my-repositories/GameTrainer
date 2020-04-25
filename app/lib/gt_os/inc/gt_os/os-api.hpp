#ifndef GAMETRAINER_OS_API_HPP
#define GAMETRAINER_OS_API_HPP

#include <gt_os/os-definitions.hpp>

namespace gt::os {
class OsApi {
  public:
    inline int getClassName([[maybe_unused]] HWND hWnd,
                            [[maybe_unused]] LPSTR lpClassName,
                            [[maybe_unused]] int nMaxCount) const {
#ifdef OS_WINDOWS
        return ::GetClassName(hWnd, lpClassName, nMaxCount);
#else
        return 1;
#endif
    }

    inline int getWindowText([[maybe_unused]] HWND hWnd,
                             [[maybe_unused]] LPSTR lpString,
                             [[maybe_unused]] int nMaxCount) const {
#ifdef OS_WINDOWS
        return ::GetWindowText(hWnd, lpString, nMaxCount);
#else
        return 1;
#endif
    }

    inline BOOL charToOem([[maybe_unused]] LPCSTR pSrc,
                          [[maybe_unused]] LPSTR pDst) const {
#ifdef OS_WINDOWS
        return ::CharToOem(pSrc, pDst);
#else
        return 1;
#endif
    }

    inline HANDLE createMutex([[maybe_unused]] LPSECURITY_ATTRIBUTES attrs,
                              [[maybe_unused]] BOOL owner,
                              [[maybe_unused]] LPCSTR name) const {
#ifdef OS_WINDOWS
        return ::CreateMutex(attrs, owner, name);
#else
        return nullptr;
#endif
    }

    inline BOOL enumWindows([[maybe_unused]] WNDENUMPROC lpEnumFunc,
                            [[maybe_unused]] LPARAM lParam) const {
#ifdef OS_WINDOWS
        return ::EnumWindows(lpEnumFunc, lParam);
#else
        return 1;
#endif
    }

    [[nodiscard]] inline DWORD getLastError() const {
#ifdef OS_WINDOWS
        return ::GetLastError();
#else
        return 0;
#endif
    }

    inline BOOL showWindow([[maybe_unused]] HWND hWnd,
                           [[maybe_unused]] int nCmdShow) const {
#ifdef OS_WINDOWS
        return ::ShowWindow(hWnd, nCmdShow);
#else
        return 1;
#endif
    }

    inline BOOL setForegroundWindow([[maybe_unused]] HWND hWnd) const {
#ifdef OS_WINDOWS
        return ::SetForegroundWindow(hWnd);
#else
        return 1;
#endif
    }

    [[nodiscard]] inline SHORT getAsyncKeyState([
        [maybe_unused]] int vKey) const {
#ifdef OS_WINDOWS
        return ::GetAsyncKeyState(vKey);
#else
        return 0;
#endif
    }

    inline BOOL
    readProcessMemory([[maybe_unused]] HANDLE hProcess,
                      [[maybe_unused]] LPCVOID lpBaseAddress,
                      [[maybe_unused]] LPVOID lpBuffer,
                      [[maybe_unused]] SIZE_T nSize,
                      [[maybe_unused]] SIZE_T *lpNumberOfBytesRead) const {
#ifdef OS_WINDOWS
        return ::ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize,
                                   lpNumberOfBytesRead);
#else
        return 1;
#endif
    }

    inline BOOL writeProcessMemory(
        [[maybe_unused]] HANDLE hProcess, [[maybe_unused]] LPVOID lpBaseAddress,
        [[maybe_unused]] LPCVOID lpBuffer, [[maybe_unused]] SIZE_T nSize,
        [[maybe_unused]] SIZE_T *lpNumberOfBytesWritten) const {
#ifdef OS_WINDOWS
        return ::WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize,
                                    lpNumberOfBytesWritten);
#else
        return 1;
#endif
    }

    [[nodiscard]] inline HANDLE
    openProcess([[maybe_unused]] DWORD dwDesiredAccess,
                [[maybe_unused]] BOOL bInheritHandle,
                [[maybe_unused]] DWORD dwProcessId) const {
#ifdef OS_WINDOWS
        return ::OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
#else
        return nullptr;
#endif
    }

    inline BOOL closeHandle([[maybe_unused]] HANDLE hObject) const {
#ifdef OS_WINDOWS
        return ::CloseHandle(hObject);
#else
        return 1;
#endif
    }

    inline HMODULE getModuleHandle([[maybe_unused]] LPCSTR lpModuleName) const {
#ifdef OS_WINDOWS
        return ::GetModuleHandle(lpModuleName);
#else
        HMODULE hModule{};
        return hModule;
#endif
    }

    inline FARPROC getProcAddress([[maybe_unused]] HMODULE hModule,
                                  [[maybe_unused]] LPCSTR lpProcName) const {
#ifdef OS_WINDOWS
        return ::GetProcAddress(hModule, lpProcName);
#else
        return nullptr;
#endif
    }
};
} // namespace gt::os

#endif // GAMETRAINER_OS_API_HPP
