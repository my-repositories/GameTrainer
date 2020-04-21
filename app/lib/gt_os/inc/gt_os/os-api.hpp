#ifndef GAMETRAINER_OS_API_HPP
#define GAMETRAINER_OS_API_HPP

#include <gt_os/os-definitions.hpp>

namespace gt::os
{
    class OsApi
    {
    public:
        inline int getClassName(HWND hWnd, LPSTR lpClassName, int nMaxCount) const {
#ifdef OS_WINDOWS
            return ::GetClassName(hWnd, lpClassName, nMaxCount);
#else
            return 1;
#endif
        }

        inline int getWindowText(HWND hWnd, LPSTR lpString, int nMaxCount) const {
#ifdef OS_WINDOWS
            return ::GetWindowText(hWnd, lpString, nMaxCount);
#else
            return 1;
#endif
        }

        inline BOOL charToOem(LPCSTR pSrc, LPSTR pDst) const {
#ifdef OS_WINDOWS
            return ::CharToOem(pSrc, pDst);
#else
            return 1;
#endif
        }

        inline HANDLE createMutex(LPSECURITY_ATTRIBUTES attrs, BOOL owner, LPCSTR name) const {
#ifdef OS_WINDOWS
            return ::CreateMutex(attrs, owner, name);
#else
            return nullptr;
#endif
        }

        inline BOOL enumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam) const {
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

        inline BOOL showWindow(HWND hWnd, int nCmdShow) const {
#ifdef OS_WINDOWS
            return ::ShowWindow(hWnd, nCmdShow);
#else
            return 1;
#endif
        }

        inline BOOL setForegroundWindow(HWND hWnd) const {
#ifdef OS_WINDOWS
            return ::SetForegroundWindow(hWnd);
#else
            return 1;
#endif
        }

        [[nodiscard]] inline SHORT getAsyncKeyState(int vKey) const {
#ifdef OS_WINDOWS
            return ::GetAsyncKeyState(vKey);
#else
            return 0;
#endif
        }

        inline BOOL readProcessMemory(
                HANDLE hProcess,
                LPCVOID lpBaseAddress,
                LPVOID lpBuffer,
                SIZE_T nSize,
                SIZE_T* lpNumberOfBytesRead
        ) const {
#ifdef OS_WINDOWS
            return ::ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
#else
            return 1;
#endif
        }


        inline BOOL writeProcessMemory(
                HANDLE hProcess,
                LPVOID lpBaseAddress,
                LPCVOID lpBuffer,
                SIZE_T nSize,
                SIZE_T* lpNumberOfBytesWritten
        ) const {
#ifdef OS_WINDOWS
            return ::WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
#else
            return 1;
#endif
        }

        [[nodiscard]] inline HANDLE openProcess(
                DWORD dwDesiredAccess,
                BOOL bInheritHandle,
                DWORD dwProcessId
        ) const {
#ifdef OS_WINDOWS
            return ::OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
#else
            return nullptr;
#endif
        }

        inline BOOL closeHandle(HANDLE hObject) const {
#ifdef OS_WINDOWS
            return ::CloseHandle(hObject);
#else
            return 1;
#endif
        }

        inline HMODULE getModuleHandle(LPCSTR lpModuleName) const {
#ifdef OS_WINDOWS
            return ::GetModuleHandle(lpModuleName);
#else
            HMODULE hModule{};
            return hModule;
#endif
        }

        inline FARPROC getProcAddress(HMODULE hModule, LPCSTR lpProcName
        ) const {
#ifdef OS_WINDOWS
            return ::GetProcAddress(hModule, lpProcName);
#else
            return nullptr;
#endif
        }
    };
}

#endif //GAMETRAINER_OS_API_HPP
