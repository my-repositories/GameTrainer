#ifndef TRAINER_H
#define TRAINER_H

#include <Game.h>

class Trainer
{
public:
    Trainer();
    ~Trainer();

    bool ChooseConfig();
    void Start();
    static bool TrainerIsRun();
    static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);
    bool GameIsRun() const;

private:
    enum Msg { MSG_WAIT_FOR_START, MSG_HOTKEYS };
    enum Sound { SOUND_OFF, SOUND_ON, SOUND_MONEY, SOUND_EXPERIENCE };

    bool bGodMode, bNoReload;
    LPSTR sound[4];
    static HWND wnd;
    Game* game;
    Config* cfg;

    bool PrintCheatTables(char* szPath) const;
    void CheckXml();
    void SetAmountValues(Config::amount& data, const std::string& type);
    void CheckHotKeys();
    void PrintMsg(Msg type);
    inline std::string GetAmount(Config::entrys& entry, Config::amount& amount);
    bool GameOnFocus() const;
    inline void Speech(Sound type) const;
    static DWORD GetProcessIdByName(const std::string& processName);
    LPSTR GetResource(int resourceId) const;
};

#endif
