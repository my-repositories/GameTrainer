#ifndef GAME_H
#define GAME_H

#include <Config.h>

class Game
{
public:
    enum POINTS_TYPE { POINTS_MONEY, POINTS_EXPERIENCE };
    enum CHEATS_TYPE { CHEAT_ONEHITKILL, CHEAT_GODMODE, CHEAT_NORELOAD };
    struct cheats
    {
        bool active;
        size_t cheatSize, offset;
        DWORD_PTR instructionAddress, returnAddress;
        PBYTE original, inject, jump;
        union ret { DWORD_PTR i; byte b[4]; } toOriginal, toInject;
        cheats() : active(false) {}
    } ohk, nr;
    Config* cfg;
    Game(Config* cfg, int pId);
    ~Game();

    bool PlayerIsDead();
    void ToggleCheat(CHEATS_TYPE type);
    void UpdateData1();
    void UpdateData2();
    void AddCurrency(POINTS_TYPE type);

private:
    union types { int i; float f; } health, money, experience;
    struct pointers { DWORD_PTR health, data1n2, money, experience, data2n1, data2n2, data2n3, temp; } ptr;
    struct previous { DWORD_PTR health, data1n2, data2n1, data2n2, data2n3; } prevPtr;
    struct maximals { int health, data1n2, data2n1, data2n2, data2n3; } max;

    HANDLE hProc;
    int pId, currentValue;
    short dwSize;
    size_t injectOffset;
    void* injectMemory;

    void InitCheats();
    void _InitCheat(cheats& cheat, Config::cheats& cfg);
    void _WriteCheat(cheats& cheat);
    void _ToggleCheat(cheats& cheat, size_t sz);
    void _ComputeBytes(cheats& cheat);
    void AddData(types& value, Config::amount& amount, Config::entrys& e, DWORD_PTR& ptr);
    void RewriteData(DWORD_PTR& prevPtr, DWORD_PTR ptr, int& freezedValue, short sz);
    DWORD_PTR GetPointer(Config::entrys& e);
    DWORD_PTR GetModule(const std::string& moduleName);
    BOOL IsWow64() const;
};

#endif
