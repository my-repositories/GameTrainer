#include <game.hpp>

namespace GameTrainer::app
{
    using namespace GameTrainer::mylib;
    Game::Game(DWORD processId)
    {
        this->processId = processId;
        this->process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->processId);
    }

    Game::~Game()
    {
        CloseHandle(this->process);
    }

    void Game::updateValue(const GameTrainer::mylib::xml::CheatEntry* entry, const float valueToAdd)
    {
//        if (temp) // "entry" == "Float"
//        {
        const DWORD_PTR ptr = this->getValueAddress(entry);
        float currentValue = 0;

        ReadProcessMemory(this->process, (LPVOID)ptr, &currentValue, entry->size, NULL);
        currentValue += valueToAdd;
        WriteProcessMemory(this->process, (LPVOID)ptr, &currentValue, entry->size, NULL);
//        }
    }

    DWORD_PTR Game::getValueAddress(const GameTrainer::mylib::xml::CheatEntry* entry) const
    {
        DWORD_PTR valueAddress;
#ifdef _WIN64
        const short dwSize = isWow64() ? 4 : 8;
#else
        const short dwSize = 4;
#endif

        auto moduleAddress = windows::getModuleAddress(entry->module, this->processId);
        auto baseAddress = moduleAddress + entry->address;
        ReadProcessMemory(this->process, (LPCVOID)baseAddress, &valueAddress, dwSize, NULL);

        if (entry->offsetsCount == -1)
        {
            return valueAddress;
        }

        for (int i = 1; i < entry->offsetsCount; i++)
        {
            auto offset = valueAddress + entry->offsets[entry->offsetsCount - i];
            ReadProcessMemory(this->process, (LPCVOID)offset, &valueAddress, dwSize, NULL);
        }

        return valueAddress + entry->offsets[0];
    }

    BOOL Game::isWow64() const
    {
        BOOL bIsWow64 = FALSE;

        typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

        LPFN_ISWOW64PROCESS fnIsWow64Process;
        fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

        if (NULL != fnIsWow64Process)
        {
            if (!fnIsWow64Process(this->process, &bIsWow64))
            {
                //handle error
            }
        }

        return bIsWow64;
    }
}
