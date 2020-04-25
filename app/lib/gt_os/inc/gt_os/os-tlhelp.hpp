#ifndef GAMETRAINER_OS_TLHELP_HPP
#define GAMETRAINER_OS_TLHELP_HPP

#include <gt_os/os-definitions.hpp>

#ifdef OS_WINDOWS
#include <TlHelp32.h>
#else
#define TH32CS_SNAPPROCESS 0x00000002
#define TH32CS_SNAPMODULE 0x00000008
#define TH32CS_SNAPMODULE32 0x00000010
#define ZeroMemory(Destination, Length) memset((Destination), 0, (Length))

typedef struct tagMODULEENTRY32 {
    DWORD dwSize;
    DWORD th32ModuleID;  // This module
    DWORD th32ProcessID; // owning process
    DWORD GlblcntUsage;  // Global usage count on the module
    DWORD ProccntUsage;  // Module usage count in th32ProcessID's context
    BYTE *modBaseAddr;   // Base address of module in th32ProcessID's context
    DWORD modBaseSize;   // Size in bytes of module starting at modBaseAddr
    HMODULE hModule; // The hModule of this module in th32ProcessID's context
    char szModule[MAX_MODULE_NAME32 + 1];
    char szExePath[MAX_PATH];
} MODULEENTRY32;

typedef struct tagPROCESSENTRY32 {
    DWORD dwSize;
    DWORD cntUsage;
    DWORD th32ProcessID; // this process
    ULONG_PTR th32DefaultHeapID;
    DWORD th32ModuleID; // associated exe
    DWORD cntThreads;
    DWORD th32ParentProcessID; // this process's parent process
    LONG pcPriClassBase;       // Base priority of process's threads
    DWORD dwFlags;
    CHAR szExeFile[MAX_PATH]; // Path
} PROCESSENTRY32;

typedef MODULEENTRY32 *LPMODULEENTRY32;
typedef PROCESSENTRY32 *LPPROCESSENTRY32;

inline HANDLE CreateToolhelp32Snapshot([[maybe_unused]] DWORD dwFlags,
                                       [[maybe_unused]] DWORD th32ProcessID) {
    return nullptr;
}

inline BOOL Module32First([[maybe_unused]] HANDLE hSnapshot,
                          [[maybe_unused]] LPMODULEENTRY32 lpme) {
    return 1;
}

inline BOOL Module32Next([[maybe_unused]] HANDLE hSnapshot,
                         [[maybe_unused]] LPMODULEENTRY32 lpme) {
    return 1;
}

inline BOOL CloseHandle([[maybe_unused]] HANDLE hObject) { return 1; }

inline BOOL Process32First([[maybe_unused]] HANDLE hSnapshot,
                           [[maybe_unused]] LPPROCESSENTRY32 lppe) {
    return 1;
}

inline BOOL Process32Next([[maybe_unused]] HANDLE hSnapshot,
                          [[maybe_unused]] LPPROCESSENTRY32 lppe) {
    return 1;
}
#endif

#endif // GAMETRAINER_OS_TLHELP_HPP
