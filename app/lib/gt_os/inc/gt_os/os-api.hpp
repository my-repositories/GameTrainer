#ifndef GAMETRAINER_OS_API_HPP
#define GAMETRAINER_OS_API_HPP

#include <gt_os/api-definitions.hpp>

namespace gt::os
{
    class OsApi
    {
    public:
        WINUSERAPI int WINAPI inline getClassName(
            _In_ HWND hWnd,
            _Out_writes_to_(nMaxCount, return) LPSTR lpClassName,
            _In_ int nMaxCount
        ) {
#ifdef OS_WINDOWS
            return ::GetClassName(hWnd, lpClassName, nMaxCount);
#else
            return 1;
#endif
        }

        WINUSERAPI int WINAPI inline getWindowText(
            _In_ HWND hWnd,
            _Out_writes_(nMaxCount) LPSTR lpString,
            _In_ int nMaxCount
        ) {
#ifdef OS_WINDOWS
            return ::GetWindowText(hWnd, lpString, nMaxCount);
#else
            return 1;
#endif
        }

        WINUSERAPI BOOL WINAPI inline charToOem(
            _In_ LPCSTR pSrc,
            _Out_writes_(_Inexpressible_(strlen(pSrc) + 1)) LPSTR pDst
        ) {
#ifdef OS_WINDOWS
            return ::CharToOem(pSrc, pDst);
#else
            return 1;
#endif
        }

        WINBASEAPI _Ret_maybenull_ HANDLE WINAPI inline createMutex(
            _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
            _In_ BOOL bInitialOwner,
            _In_opt_ LPCSTR lpName
        ) {
#ifdef OS_WINDOWS
            return ::CreateMutex(lpMutexAttributes, bInitialOwner, lpName);
#else
            return nullptr;
#endif
        }

        WINUSERAPI BOOL WINAPI inline enumWindows(
            _In_ WNDENUMPROC lpEnumFunc,
            _In_ LPARAM lParam
        ) {
#ifdef OS_WINDOWS
            return ::EnumWindows(lpEnumFunc, lParam);
#else
            return 1;
#endif
        }

        WINBASEAPI _Check_return_ _Post_equals_last_error_ DWORD WINAPI getLastError(VOID) {
#ifdef OS_WINDOWS
            return ::GetLastError();
#else
            return 0;
#endif
        }

        WINUSERAPI BOOL WINAPI showWindow(_In_ HWND hWnd, _In_ int nCmdShow) {
#ifdef OS_WINDOWS
            return ::ShowWindow(hWnd, nCmdShow);
#else
            return 1;
#endif
        }

        WINUSERAPI BOOL WINAPI setForegroundWindow(_In_ HWND hWnd) {
#ifdef OS_WINDOWS
            return ::SetForegroundWindow(hWnd);
#else
            return 1;
#endif
        }
    };
}

#endif //GAMETRAINER_OS_API_HPP
