#ifndef GAMETRAINER_OS_API_HPP
#define GAMETRAINER_OS_API_HPP

#include <gt_os/os-definitions.hpp>

namespace gt::os
{
    class OsApi
    {
    public:
        inline WINUSERAPI int WINAPI getClassName(
            _In_ HWND hWnd,
            _Out_writes_to_(nMaxCount, return) LPSTR lpClassName,
            _In_ int nMaxCount
        ) const {
#ifdef OS_WINDOWS
            return ::GetClassName(hWnd, lpClassName, nMaxCount);
#else
            return 1;
#endif
        }

        inline WINUSERAPI int WINAPI getWindowText(
            _In_ HWND hWnd,
            _Out_writes_(nMaxCount) LPSTR lpString,
            _In_ int nMaxCount
        ) const {
#ifdef OS_WINDOWS
            return ::GetWindowText(hWnd, lpString, nMaxCount);
#else
            return 1;
#endif
        }

        inline WINUSERAPI BOOL WINAPI charToOem(
            _In_ LPCSTR pSrc,
            _Out_writes_(_Inexpressible_(strlen(pSrc) + 1)) LPSTR pDst
        ) const {
#ifdef OS_WINDOWS
            return ::CharToOem(pSrc, pDst);
#else
            return 1;
#endif
        }

        inline WINBASEAPI _Ret_maybenull_ HANDLE WINAPI createMutex(
            _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
            _In_ BOOL bInitialOwner,
            _In_opt_ LPCSTR lpName
        ) const {
#ifdef OS_WINDOWS
            return ::CreateMutex(lpMutexAttributes, bInitialOwner, lpName);
#else
            return nullptr;
#endif
        }

        inline WINUSERAPI BOOL WINAPI enumWindows(
            _In_ WNDENUMPROC lpEnumFunc,
            _In_ LPARAM lParam
        ) const {
#ifdef OS_WINDOWS
            return ::EnumWindows(lpEnumFunc, lParam);
#else
            return 1;
#endif
        }

        inline WINBASEAPI _Check_return_ _Post_equals_last_error_ DWORD WINAPI
        getLastError(VOID) const {
#ifdef OS_WINDOWS
            return ::GetLastError();
#else
            return 0;
#endif
        }

        inline WINUSERAPI BOOL WINAPI showWindow(_In_ HWND hWnd, _In_ int nCmdShow) const {
#ifdef OS_WINDOWS
            return ::ShowWindow(hWnd, nCmdShow);
#else
            return 1;
#endif
        }

        inline WINUSERAPI BOOL WINAPI setForegroundWindow(_In_ HWND hWnd) const {
#ifdef OS_WINDOWS
            return ::SetForegroundWindow(hWnd);
#else
            return 1;
#endif
        }

        [[nodiscard]] inline WINUSERAPI SHORT WINAPI getAsyncKeyState(_In_ int vKey) const {
#ifdef OS_WINDOWS
            return ::GetAsyncKeyState(vKey);
#else
            return 0;
#endif
        }

        inline WINBASEAPI _Success_(return != FALSE) BOOL WINAPI readProcessMemory(
                _In_ HANDLE hProcess,
                _In_ LPCVOID lpBaseAddress,
                _Out_writes_bytes_to_(nSize,*lpNumberOfBytesRead) LPVOID lpBuffer,
                _In_ SIZE_T nSize,
                _Out_opt_ SIZE_T* lpNumberOfBytesRead
        ) const {
#ifdef OS_WINDOWS
            return ::ReadProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesRead);
#else
            return 1;
#endif
        }


        inline WINBASEAPI _Success_(return != FALSE) BOOL WINAPI writeProcessMemory(
                _In_ HANDLE hProcess,
                _In_ LPVOID lpBaseAddress,
                _In_reads_bytes_(nSize) LPCVOID lpBuffer,
                _In_ SIZE_T nSize,
                _Out_opt_ SIZE_T* lpNumberOfBytesWritten
        ) const {
#ifdef OS_WINDOWS
            return ::WriteProcessMemory(hProcess, lpBaseAddress, lpBuffer, nSize, lpNumberOfBytesWritten);
#else
            return 1;
#endif
        }

        [[nodiscard]] inline WINBASEAPI HANDLE WINAPI openProcess(
                _In_ DWORD dwDesiredAccess,
                _In_ BOOL bInheritHandle,
                _In_ DWORD dwProcessId
        ) const {
#ifdef OS_WINDOWS
            return ::OpenProcess(dwDesiredAccess, bInheritHandle, dwProcessId);
#else
            return nullptr;
#endif
        }

        inline WINBASEAPI BOOL WINAPI closeHandle(_In_ _Post_ptr_invalid_ HANDLE hObject) const {
#ifdef OS_WINDOWS
            return ::CloseHandle(hObject);
#else
            return 1;
#endif
        }

        inline WINBASEAPI
        _When_(lpModuleName == NULL,_Ret_notnull_)
        _When_(lpModuleName != NULL,_Ret_maybenull_)
        HMODULE WINAPI
        getModuleHandle(_In_opt_ LPCSTR lpModuleName) const {
#ifdef OS_WINDOWS
            return ::GetModuleHandle(lpModuleName);
#else
            HMODULE hModule{};
            return hModule;
#endif
        }

        inline WINBASEAPI FARPROC WINAPI getProcAddress(
                _In_ HMODULE hModule,
                _In_ LPCSTR lpProcName
        ) const {
#ifdef OS_WINDOWS
            return ::GetProcAddress(hModule, lpProcName);
#else
            return 1;
#endif
        }
    };
}

#endif //GAMETRAINER_OS_API_HPP
