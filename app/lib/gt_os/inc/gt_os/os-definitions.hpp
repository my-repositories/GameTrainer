#ifndef GAMETRAINER_OS_DEFINITIONS_HPP
#define GAMETRAINER_OS_DEFINITIONS_HPP

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS
#endif

#ifdef OS_WINDOWS
#include <Windows.h>
#else
#define far
#define FAR far
#define SW_RESTORE 9
#ifndef NULL
#define NULL 0
#endif
#ifndef MAX_PATH
#define MAX_PATH 255
#endif
#define FALSE 0
#define TRUE 1
#define VK_SHIFT 0
#define VK_CONTROL 0
#define VK_MENU 0
#define VK_F13 0
#define VK_RETURN 0
#define VK_SPACE 0
#define SND_APPLICATION 0x0080
#define SND_ASYNC 0x0001
#define SND_NODEFAULT 0x0002
#define MAX_MODULE_NAME32 255
#define ERROR_ALREADY_EXISTS 183L
#define __TEXT(quote) quote
#define TEXT(quote) __TEXT(quote)
#define STANDARD_RIGHTS_REQUIRED         (0x000F0000L)
#define SYNCHRONIZE                      (0x00100000L)
#define PROCESS_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
                                   0xFFFF)

#define CHAR char
#define BYTE unsigned char
#define SHORT short
#define BOOL int
#define PBOOL int*
#define LPARAM long
#define LONG long
#define UINT unsigned int
#define size_t unsigned int
#define DWORD unsigned long
#define MCIERROR unsigned long
#define ULONG_PTR unsigned long
#define LPVOID void*
#define LPCVOID const void*
#define HANDLE void*
#define LPSTR char*
#define LPCSTR const char*
#define VOID void

#define _Ret_maybenull_
#define _Check_return_
#define _Post_equals_last_error_
#define WINAPI
#define WINBASEAPI
#define WINMMAPI
#define WINUSERAPI
#define CALLBACK
#define _Post_ptr_invalid_
#define _In_
#define _In_opt_
#define _In_reads_bytes_(size)
#define _Inout_updates_z_(size)
#define _Out_opt_
#define _Out_writes_to_(size,count)
#define _Out_writes_to_opt_(size,count)
#define _Out_writes_opt_(size)
#define _Out_writes_bytes_to_(size,count)
#define _Out_writes_(size)
#define _Success_(expr)
#define _When_(expr, annos)

#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
DECLARE_HANDLE (HWND);
DECLARE_HANDLE(HINSTANCE);

typedef ULONG_PTR DWORD_PTR, SIZE_T;
typedef HINSTANCE HMODULE;
typedef BOOL (CALLBACK* WNDENUMPROC)(HWND, LPARAM);
typedef int (FAR WINAPI *FARPROC)();

typedef struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
} SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

inline WINMMAPI BOOL WINAPI PlaySoundA(
    _In_opt_ LPCSTR pszSound,
    _In_opt_ HMODULE hmod,
    _In_ DWORD fdwSound
    ) {
    return 0;
}

inline WINMMAPI MCIERROR WINAPI mciSendString(
    _In_ LPCSTR lpstrCommand,
    _Out_writes_opt_(uReturnLength) LPSTR lpstrReturnString,
    _In_ UINT uReturnLength,
    _In_opt_ HWND hwndCallback
    ) {
    return 0;
}

inline WINBASEAPI VOID WINAPI Sleep(_In_ DWORD dwMilliseconds) {}

inline WINBASEAPI BOOL WINAPI SetConsoleTitle(_In_ LPCSTR lpConsoleTitle) {
    return 0;
}

inline WINBASEAPI _Success_(return != 0 && return < nBufferLength) DWORD WINAPI
GetCurrentDirectory(
    _In_ DWORD nBufferLength,
    _Out_writes_to_opt_(nBufferLength,return + 1) LPSTR lpBuffer
) {
    return 1;
}

inline WINBASEAPI LPSTR WINAPI lstrcat(
    _Inout_updates_z_(_String_length_(lpString1) + _String_length_(lpString2) + 1) LPSTR lpString1,
    _In_    LPCSTR lpString2
    ) {
    return nullptr;
}
#endif

#endif //GAMETRAINER_OS_DEFINITIONS_HPP
