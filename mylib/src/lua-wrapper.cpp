#include <lua-wrapper.hpp>

namespace GameTrainer::mylib
{
    LuaWrapper::LuaWrapper()
    {
        this->field = 24;
    }

    int LuaWrapper::method(const int x) {
        this->field = x + this->field;
        return this->field;
    }

    void execute()
    {
        lua_State* L = luaL_newstate();
        constexpr char* LUA_FILE = (char*)R"(
processName = 'KillingFloor.exe'

maxHealth = 100

keys = {}
keys.size = 2
keys.registered = {77, 13}
registeredKeys = {77, 13}
perks = { 'bers', 'medic', 'support', 'commando', 'sharpshooter', 'demolition', 'firebug' }
		)";

        luaL_dostring(L, LUA_FILE);

        std::vector<int> registeredKeys;
        setVector(registeredKeys, L, "registeredKeys");
        for (int i = 0; i < registeredKeys.size(); ++i)
        {
            std::cout << i << ": " << registeredKeys[i] << std::endl;
        }

        std::vector<char*> perks;
        setVector(perks, L, "perks");
        for (int i = 0; i < perks.size(); ++i)
        {
            std::cout << i << ": " << perks[i] << std::endl;
        }

        char* processName = nullptr;
        setValue(processName, L, "processName");
        if (processName != nullptr)
        {
            std::cout << processName << std::endl;
            std::cout << processName << std::endl;
            std::cout << processName << std::endl;
        }

        int maxHealth;
        setValue(maxHealth, L, "maxHealth");
        if (maxHealth)
        {
            std::cout << maxHealth << std::endl;
            std::cout << maxHealth << std::endl;
            std::cout << maxHealth << std::endl;
        }

        lua_close(L);
    }
}
