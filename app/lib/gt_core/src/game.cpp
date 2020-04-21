#include <gt_core/game.hpp>

namespace gt::core
{
    Game::Game(DWORD processId)
    {
        this->processId = processId;
        this->process = this->osApi.openProcess(PROCESS_ALL_ACCESS, FALSE, this->processId); // NOLINT(hicpp-signed-bitwise)
    }

    Game::~Game()
    {
        this->osApi.closeHandle(this->process);
    }

    void Game::updateValue(const gt::xml::CheatEntry* entry, const float valueToAdd)
    {
//        if (temp) // "entry" == "Float"
//        {
        const DWORD_PTR ptr = this->getValueAddress(entry);
        float currentValue = 0;

        this->osApi.readProcessMemory(this->process, (LPVOID)ptr, &currentValue, entry->size, nullptr);
        currentValue += valueToAdd;
        this->osApi.writeProcessMemory(this->process, (LPVOID)ptr, &currentValue, entry->size, nullptr);
//        }
    }

    DWORD_PTR Game::getValueAddress(const gt::xml::CheatEntry* entry) const
    {
        DWORD valueAddress;
#ifdef _WIN64
        const short dwSize = this->isWow64() ? 4 : 8;
#else
        const short dwSize = 4;
#endif

        auto moduleAddress = os::getModuleAddress(entry->module, this->processId);
        auto baseAddress = moduleAddress + entry->address;
        this->osApi.readProcessMemory(this->process, (LPCVOID)baseAddress, &valueAddress, dwSize, nullptr);

        if (entry->offsetsCount == -1)
        {
            return valueAddress;
        }

        for (int i = 1; i < entry->offsetsCount; i++)
        {
            DWORD_PTR offset = valueAddress + entry->offsets[entry->offsetsCount - i];
            this->osApi.readProcessMemory(this->process, (LPCVOID)offset, &valueAddress, dwSize, nullptr);
        }

        return valueAddress + entry->offsets[0];
    }

    BOOL Game::isWow64() const
    {
        BOOL bIsWow64 = FALSE;

        typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

        LPFN_ISWOW64PROCESS fnIsWow64Process;
        fnIsWow64Process = (LPFN_ISWOW64PROCESS)this->osApi.getProcAddress(this->osApi.getModuleHandle(TEXT("kernel32")), "IsWow64Process");

        if (nullptr != fnIsWow64Process)
        {
            if (!fnIsWow64Process(this->process, &bIsWow64))
            {
                //handle error
            }
        }

        return bIsWow64;
    }
}
