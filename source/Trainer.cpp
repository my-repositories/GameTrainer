#include <Trainer.h>
#include <Game.h>
#include <resource.h>
#include <TlHelp32.h>
#pragma comment(lib,"Winmm.lib")
// [console version]
#include <iostream>
#include <sstream>
#include <iomanip>
// [/console version]

HWND Trainer::wnd = NULL;

Trainer::Trainer()
{
    sound[0] = GetResource(SND_OFF);
    sound[1] = GetResource(SND_ON);
    sound[2] = GetResource(SND_MONEY);
    sound[3] = GetResource(SND_EXPERIENCE);
    bGodMode = false;
    bNoReload = false;

    SetConsoleTitle("GameTrainer+");
    // SetWindowText()
    // [console version]
    system("color a");
    // [/console version]
}

Trainer::~Trainer()
{
    delete cfg;
    delete game;
}

// [console version]
bool Trainer::ChooseConfig()
{
    char cfgDir[MAX_PATH], szPath[MAX_PATH];
    GetCurrentDirectory(sizeof(cfgDir), cfgDir);
    lstrcat(cfgDir, "\\Games\\");
    memcpy(szPath, cfgDir, MAX_PATH);
    lstrcat(szPath, "*.*");

    if (!PrintCheatTables(szPath))
        return false;

    // Select CheatTable file
    std::cout << std::endl;
    std::string fileName;
    do
    {
        std::cout << "Enter CheatTable name:" << std::endl;
        std::cin >> fileName;
        memcpy(szPath, cfgDir, MAX_PATH);
        lstrcat(szPath, fileName.c_str());
    } while (!Config::FileExists(szPath));

    cfg = new Config(szPath);
    CheckXml();
    CheckHotKeys();

    std::string title = cfg->processName;
    SetConsoleTitle(title.append(" - GameTrainer+").c_str());
    // SetWindowText()
    PrintMsg(MSG_WAIT_FOR_START);
    return true;
}

bool Trainer::PrintCheatTables(char* szPath) const
{
    // Step 1: Find config files
    WIN32_FIND_DATA ffd;
    HANDLE hFind = FindFirstFile(szPath, &ffd);
    if (hFind == INVALID_HANDLE_VALUE)
    {
        std::cout << "Config files was not found." << std::endl;
        system("pause");
        return false;
    }

    // Step 2: Print config list
    std::cout << "Config list:\n" << std::endl;
    do
    {
        if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            std::cout << ffd.cFileName << std::endl;
        }
    } while (FindNextFile(hFind, &ffd));
    FindClose(hFind);
    return true;
}

void Trainer::CheckXml()
{
    if (cfg->processName == "")
    {
        std::cout << "Enter procces name:" << std::endl;
        std::cin >> cfg->processName;
    }
    if (cfg->maxHealth.type == "")
    {
        std::cout << "Enter max health:" << std::endl;
        SetAmountValues(cfg->maxHealth, cfg->health.type);
    }
    if (cfg->money.size != 0 && cfg->amountMoney.type == "")
    {
        std::cout << "Enter amount of added Data3:" << std::endl;
        SetAmountValues(cfg->amountMoney, cfg->money.type);
    }
    if (cfg->experience.size != 0 && cfg->amountExperience.type == "")
    {
        std::cout << "Enter amount of added Data4:" << std::endl;
        SetAmountValues(cfg->amountExperience, cfg->experience.type);
    }
}

void Trainer::SetAmountValues(Config::amount& data, const std::string& type)
{
    if (type == "Float")
        std::cin >> data.value.f;
    else
        std::cin >> data.value.i;
}

void Trainer::CheckHotKeys()
{
    if (cfg->hotkey.data1.code != -1 && cfg->hotkey.data1.name != "")
        return;

    cfg->hotkey.data1.name = "F6";
    cfg->hotkey.data1.code = VK_F6;

    cfg->hotkey.data2.name = "F7";
    cfg->hotkey.data2.code = VK_F7;

    cfg->hotkey.money.name = "F8";
    cfg->hotkey.money.code = VK_F8;

    cfg->hotkey.experience.name = "F9";
    cfg->hotkey.experience.code = VK_F9;

    cfg->hotkey.ohk.name = "NUM0";
    cfg->hotkey.ohk.code = VK_NUMPAD0;

    cfg->hotkey.nr.name = "NUM1";
    cfg->hotkey.nr.code = VK_NUMPAD1;
}

void Trainer::PrintMsg(Msg type)
{
    system("cls");
    std::cout << std::endl << std::endl << std::endl
        << "\t$$$$$$_$$$$$___$$$$__$$$$$$_$$__$$_$$$$$__$$$$$" << std::endl
        << "\t__$$___$$__$$_$$__$$___$$___$$$_$$_$$_____$$__$$_______$$" << std::endl
        << "\t__$$___$$$$$__$$$$$$___$$___$$_$$$_$$$$___$$$$$______$$$$$$" << std::endl
        << "\t__$$___$$__$$_$$__$$___$$___$$__$$_$$_____$$__$$_______$$" << std::endl
        << "\t__$$___$$__$$_$$__$$_$$$$$$_$$__$$_$$$$$__$$__$$" << std::endl
        << std::endl << std::endl << std::endl << std::endl;

    if (type == MSG_WAIT_FOR_START)
    {
        std::cout
            << "\t\t\t Waiting for start:" << std::endl
            << "\t\t\t " << cfg->processName << std::endl;
    }
    else if (type == MSG_HOTKEYS)
    {
        std::cout << "\t\t\t "
            << cfg->hotkey.data1.name
            << " - toggle GodMode" << std::endl;

        if (cfg->data2n1.size != 0 || cfg->data2n2.size != 0 || cfg->data2n3.size != 0)
            std::cout << "\t\t\t "
            << cfg->hotkey.data2.name
            << " - toggle NoReload" << std::endl;

        if (cfg->money.size != 0)
            std::cout << "\t\t\t "
            << cfg->hotkey.money.name
            << " - increase "
            << GetAmount(cfg->money, cfg->amountMoney)
            << " Money" << std::endl;

        if (cfg->experience.size != 0)
            std::cout << "\t\t\t "
            << cfg->hotkey.experience.name
            << " - increase "
            << GetAmount(cfg->experience, cfg->amountExperience)
            << " Experience" << std::endl;

        if (cfg->ohk.exists)
            std::cout << "\t\t\t "
            << cfg->hotkey.ohk.name
            << " - toggle One Hit Kill" << std::endl;

        if (cfg->nr.exists)
            std::cout << "\t\t\t "
            << cfg->hotkey.nr.name
            << " - toggle No Reload" << std::endl;
    }
}

inline std::string Trainer::GetAmount(Config::entrys& entry, Config::amount& amount)
{
    std::stringstream ss;
    if (entry.type == "Float")
    {
        ss << std::fixed << std::setprecision(2) << amount.value.f;
    }
    else
    {
        ss << amount.value.i;
    }

    return ss.str();
}
// [/console version]

void Trainer::Start()
{
    game = new Game(cfg, GetProcessIdByName(cfg->processName));
    PrintMsg(MSG_HOTKEYS);
    while (true)
    {
        // Close Trainer IF GAME is NOT RUNNING
        if (!GameIsRun())
        {
            break;
        }

        // Continue IF GAME is not active || PLAYER is DEAD
        if (!GameOnFocus() || game->PlayerIsDead())
        {
            Sleep(1000);
            continue;
        }

        // Rewrite data if FREEZE FLAG enabled
        if (bGodMode)
        {
            game->UpdateData1();
        }
        if (bNoReload)
        {
            game->UpdateData2();
        }

        // Keyboard handling
        if (GetAsyncKeyState(cfg->hotkey.data1.code) & 1)
        {
            bGodMode = !bGodMode;
            Speech(bGodMode ? SOUND_ON : SOUND_OFF);
        }
        if (GetAsyncKeyState(cfg->hotkey.data2.code) & 1)
        {
            bNoReload = !bNoReload;
            Speech(bNoReload ? SOUND_ON : SOUND_OFF);
        }
        if (cfg->money.size != 0 && GetAsyncKeyState(cfg->hotkey.money.code) & 1)
        {
            game->AddCurrency(Game::POINTS_MONEY);
            Speech(SOUND_MONEY);
        }
        if (cfg->experience.size != 0 && GetAsyncKeyState(cfg->hotkey.experience.code) & 1)
        {
            game->AddCurrency(Game::POINTS_EXPERIENCE);
            Speech(SOUND_EXPERIENCE);
        }
        if (cfg->ohk.exists && GetAsyncKeyState(cfg->hotkey.ohk.code) & 1)
        {
            game->ToggleCheat(Game::CHEAT_ONEHITKILL);
            Speech(game->ohk.active ? SOUND_ON : SOUND_OFF);
        }
        if (cfg->nr.exists && GetAsyncKeyState(cfg->hotkey.nr.code) & 1)
        {
            game->ToggleCheat(Game::CHEAT_NORELOAD);
            Speech(game->nr.active ? SOUND_ON : SOUND_OFF);
        }
        Sleep(50);
    }
}

bool Trainer::TrainerIsRun()
{
    HANDLE mutex = CreateMutex(NULL, TRUE, "GameTrainer+");

    if (mutex == NULL || GetLastError() == ERROR_ALREADY_EXISTS)
    {
        if (EnumWindows(&EnumWindowsProc, NULL) && wnd != NULL)
        {
            ShowWindow(wnd, SW_RESTORE);
            SetForegroundWindow(wnd);
            return true;
        }
    }

    return false;
}

BOOL CALLBACK Trainer::EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char szTextWin[255]; DWORD dwPID = NULL;
    if (GetWindowText(hwnd, szTextWin, sizeof(szTextWin)))
    {
        CharToOem(szTextWin, szTextWin);
        if (std::string::npos != ((std::string)szTextWin).find("GameTrainer+"))
        {
            szTextWin[0] = '\0';
            if (GetClassName(hwnd, szTextWin, sizeof(szTextWin)))
            {
                if ((std::string)"ConsoleWindowClass" == (std::string)szTextWin)
                    wnd = hwnd;
            }
        }
    }
    szTextWin[0] = '\0';
    return TRUE;
}

bool Trainer::GameOnFocus() const
{
    DWORD idActive;
    GetWindowThreadProcessId(GetForegroundWindow(), &idActive);
    return idActive == GetProcessIdByName(cfg->processName);
}

inline void Trainer::Speech(Sound type) const
{
    sndPlaySound(sound[type], SND_MEMORY | SND_ASYNC | SND_NODEFAULT);
}

bool Trainer::GameIsRun() const
{
    return 0 != GetProcessIdByName(cfg->processName);
}

DWORD Trainer::GetProcessIdByName(const std::string& processName)
{
    DWORD pid = 0;

    // Create toolhelp snapshot
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    // Walkthrough all processes
    if (Process32First(snapshot, &process))
    {
        do
        {
            // Compare process.szExeFile based on format of name, i.e., trim file path
            // trim .exe if necessary, etc
            if (processName == static_cast<std::string>(process.szExeFile))
            {
                pid = process.th32ProcessID;
                break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);
    return pid;
}

// MSDN.function
LPSTR Trainer::GetResource(int resourceId) const
{
    HMODULE hInst = GetModuleHandle(NULL);
    if (!hInst)
    {
        return FALSE;
    }
    LPSTR lpRes;
    HANDLE hResInfo, hRes;

    // Find the WAVE resource. 

    hResInfo = FindResource(hInst, MAKEINTRESOURCE(resourceId), "WAVE");
    if (hResInfo == NULL)
        return FALSE;

    // Load the WAVE resource. 

    hRes = LoadResource(hInst, (HRSRC)hResInfo);
    if (hRes == NULL)
        return FALSE;

    // Lock the WAVE resource and play it. 

    lpRes = (LPSTR)LockResource(hRes);
    if (lpRes != NULL)
    {
        UnlockResource(hRes);
    }

    // Free the WAVE resource and return success or failure. 

    FreeResource(hRes);
    return lpRes;
}
