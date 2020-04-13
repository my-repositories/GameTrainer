#ifndef GAMETRAINER_API_DEFINITIONS_HPP
#define GAMETRAINER_API_DEFINITIONS_HPP

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
#define OS_WINDOWS
#endif

#ifdef OS_WINDOWS
#include <Windows.h>
#else
#define SW_RESTORE 9
#define NULL 0
#define FALSE 0
#define TRUE 1
#define ERROR_ALREADY_EXISTS 183L

#define BOOL int
#define LPARAM long
#define DWORD unsigned long
#define HANDLE void*
#define LPSTR char*
#define VOID void

#define _Ret_maybenull_
#define _Check_return_
#define _Post_equals_last_error_
#define WINAPI
#define WINBASEAPI
#define WINUSERAPI
#define CALLBACK
#define _In_
#define _Out_writes_to_(size,count)

#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
DECLARE_HANDLE (HWND);
#endif

#endif //GAMETRAINER_API_DEFINITIONS_HPP
