#include <Trainer.h>
#include <Game.h>
#include <TlHelp32.h>

Game::Game(Config* cfg, int pId)
{
    this->cfg = cfg;
    this->pId = pId;
    hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);

#ifdef _WIN64
    dwSize = IsWow64() ? 4 : 8;
#else
    dwSize = 4;
#endif

    InitCheats();
}

Game::~Game()
{
    VirtualFreeEx(hProc, injectMemory, 0, MEM_RELEASE);
    CloseHandle(hProc);
}

bool Game::PlayerIsDead()
{
    ptr.health = GetPointer(cfg->health);

    if (cfg->health.type == "Float")
    {
        ReadProcessMemory(hProc, (LPVOID)ptr.health, &health.f, cfg->health.size, NULL);
        return health.f <= 0 || health.f > cfg->maxHealth.value.f;
    }

    ReadProcessMemory(hProc, (LPVOID)ptr.health, &health.i, cfg->health.size, NULL);
    return health.i <= 0 || health.i > cfg->maxHealth.value.i;
}

void Game::InitCheats()
{
    if (cfg->ohk.exists)
    {
        _InitCheat(ohk, cfg->ohk);
    }
    if (cfg->nr.exists)
    {
        _InitCheat(nr, cfg->nr);
    }

    injectMemory = VirtualAllocEx
    (
        hProc,
        NULL,
        ohk.cheatSize + nr.cheatSize,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_EXECUTE_READWRITE
    );

    if (cfg->ohk.exists)
    {
        _WriteCheat(ohk);
    }
    if (cfg->nr.exists)
    {
        _WriteCheat(nr);
    }
}

void Game::_InitCheat(cheats& cheat, Config::cheats& cfg)
{
    cheat.instructionAddress = GetModule(cfg.instructionModule) + cfg.instructionAddress;
    cheat.returnAddress = GetModule(cfg.returnModule) + cfg.returnAddress;
    cheat.cheatSize = cfg.inject.size();

    cheat.original = &cfg.original[0];
    cheat.jump = &cfg.jump[0];
    cheat.inject = &cfg.inject[0];
}

void Game::_WriteCheat(cheats& cheat)
{
    cheat.offset = injectOffset;
    _ComputeBytes(cheat);

    WriteProcessMemory
    (
        hProc,
        (LPVOID)((DWORD_PTR)injectMemory + injectOffset),
        cheat.inject,
        cheat.cheatSize,
        NULL
    );
    injectOffset += cheat.cheatSize;
}

void Game::ToggleCheat(CHEATS_TYPE type)
{
    switch (type)
    {
    case CHEAT_ONEHITKILL:
        _ToggleCheat(ohk, cfg->ohk.original.size());
        break;

    case CHEAT_NORELOAD:
        _ToggleCheat(nr, cfg->nr.original.size());
        break;
    }

}

void Game::_ToggleCheat(cheats& cheat, size_t sz)
{
    if (injectMemory == NULL)
    {
        return;
    }
    if (cheat.active)
    {
        WriteProcessMemory(hProc, (LPVOID)cheat.instructionAddress, cheat.original, sz, NULL);
    }
    else
    {
        WriteProcessMemory(hProc, (LPVOID)cheat.instructionAddress, cheat.jump, sz, NULL);
    }
    cheat.active = !cheat.active;
}

void Game::_ComputeBytes(cheats& cheat)
{
    cheat.toOriginal.i = (DWORD_PTR)injectMemory + cheat.offset - cheat.instructionAddress - 5;
    for (int i = 0; i < 4; i++)
        cheat.jump[1 + i] = cheat.toOriginal.b[i];

    cheat.toInject.i = cheat.returnAddress - (cheat.cheatSize - 5 + (DWORD_PTR)injectMemory + cheat.offset) - 5;
    for (int i = 0; i < 4; i++)
        cheat.inject[cheat.cheatSize - 4 + i] = cheat.toInject.b[i];
}

void Game::UpdateData1()
{
    RewriteData(prevPtr.health, ptr.health, max.health, cfg->health.size);

    if (cfg->data1n2.size != 0)
    {
        ptr.data1n2 = GetPointer(cfg->data1n2);
        RewriteData(prevPtr.data1n2, ptr.data1n2, max.data1n2, cfg->data1n2.size);
    }
}

void Game::UpdateData2()
{
    if (cfg->data2n1.size != 0)
    {
        ptr.data2n1 = GetPointer(cfg->data2n1);
        RewriteData(prevPtr.data2n1, ptr.data2n1, max.data2n1, cfg->data2n1.size);
    }

    if (cfg->data2n2.size != 0)
    {
        ptr.data2n2 = GetPointer(cfg->data2n2);
        RewriteData(prevPtr.data2n2, ptr.data2n2, max.data2n2, cfg->data2n2.size);
    }

    if (cfg->data2n3.size != 0)
    {
        ptr.data2n3 = GetPointer(cfg->data2n3);
        RewriteData(prevPtr.data2n3, ptr.data2n3, max.data2n3, cfg->data2n3.size);
    }
}

void Game::AddCurrency(POINTS_TYPE type)
{
    switch (type)
    {
    case POINTS_MONEY:
        AddData(money, cfg->amountMoney, cfg->money, ptr.money);
        break;
    case POINTS_EXPERIENCE:
        AddData(experience, cfg->amountExperience, cfg->experience, ptr.experience);
        break;
    }
}

void Game::AddData(types& value, Config::amount& amount, Config::entrys& e, DWORD_PTR& ptr)
{
    ptr = GetPointer(e);
    if (e.type == "Float")
    {
        ReadProcessMemory(hProc, (LPVOID)ptr, &value.f, e.size, NULL);
        value.f += amount.value.f;
        WriteProcessMemory(hProc, (LPVOID)ptr, &value.f, e.size, NULL);
    }
    else
    {
        ReadProcessMemory(hProc, (LPVOID)ptr, &value.i, e.size, NULL);
        value.i += amount.value.i;
        WriteProcessMemory(hProc, (LPVOID)ptr, &value.i, e.size, NULL);
    }
}

void Game::RewriteData(DWORD_PTR& prevPtr, DWORD_PTR ptr, int& freezedValue, short sz)
{
    if (prevPtr != ptr)
    {
        prevPtr = ptr;
        ReadProcessMemory(hProc, (LPVOID)ptr, &freezedValue, sz, NULL);
        return;
    }

    ReadProcessMemory(hProc, (LPCVOID)ptr, &currentValue, sz, NULL);

    if (freezedValue > currentValue)
    {
        WriteProcessMemory(hProc, (LPVOID)ptr, &freezedValue, sz, NULL);
    }
    else
    {
        freezedValue = currentValue;
    }
}

DWORD_PTR Game::GetPointer(Config::entrys& e)
{
    ReadProcessMemory(hProc, (LPCVOID)(GetModule(e.module) + e.address), &ptr.temp, dwSize, NULL);

    if (e.count == -1)
    {
        return ptr.temp;
    }
    for (int i = 0; i < e.count; i++)
    {
        ReadProcessMemory(hProc, (LPCVOID)(ptr.temp + e.offsets[e.count - i]), &ptr.temp, dwSize, NULL);
    }
    return ptr.temp + e.offsets[0];
}

DWORD_PTR Game::GetModule(const std::string& moduleName)
{
    MODULEENTRY32 lpModuleEntry = { 0 };
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pId);

    if (!hSnapShot)
        return NULL;
    lpModuleEntry.dwSize = sizeof(lpModuleEntry);
    BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);
    while (bModule)
    {
        if (moduleName == static_cast<std::string>(lpModuleEntry.szModule))
        {
            CloseHandle(hSnapShot);
            return (DWORD_PTR)lpModuleEntry.modBaseAddr;
        }
        bModule = Module32Next(hSnapShot, &lpModuleEntry);
    }
    CloseHandle(hSnapShot);
    return NULL;
}

BOOL Game::IsWow64() const
{
    BOOL bIsWow64 = FALSE;

    typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

    LPFN_ISWOW64PROCESS fnIsWow64Process;
    fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
        GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

    if (NULL != fnIsWow64Process)
    {
        if (!fnIsWow64Process(hProc, &bIsWow64))
        {
            //handle error
        }
    }
    return bIsWow64;
}