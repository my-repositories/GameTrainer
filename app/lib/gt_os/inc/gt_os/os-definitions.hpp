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
#define FALSE 0
#define TRUE 1
#define ERROR_ALREADY_EXISTS 183L
#define __TEXT(quote) quote
#define TEXT(quote) __TEXT(quote)
#define PROCESS_ALL_ACCESS        (STANDARD_RIGHTS_REQUIRED | SYNCHRONIZE | \
                                   0xFFFF)

#define SHORT short
#define BOOL int
#define LPARAM long
#define DWORD unsigned long
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
#define WINUSERAPI
#define CALLBACK
#define _Post_ptr_invalid_
#define _In_
#define _In_opt_
#define _In_reads_bytes_(size)
#define _Out_opt_
#define _Out_writes_to_(size,count)
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
#endif

#endif //GAMETRAINER_OS_DEFINITIONS_HPP
