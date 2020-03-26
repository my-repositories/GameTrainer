#include <functional>
#include <iostream>
#include <Windows.h>

#include <gg.hpp>
#include <lua-wrapper.hpp>

#define KEY_Q 0x51

void loadLuaState(GameTrainer::mylib::LuaWrapper& lua);

int main(int argc, char* argv[])
{
    std::string title = std::string(MY_PROJECT_NAME) + " " + MY_PROJECT_VERSION;
    SetConsoleTitle(title.c_str());

#if !DEBUG
    system("color a");
#endif

    GameTrainer::mylib::LuaWrapper lua;
    loadLuaState(lua);

    lua.registerFunction("writeMemory", [](const char* mem)
    {
        std::cout << "write memory: " << mem << std::endl;
    });

    lua.registerFunction("playSound", [](const char* sound)
    {
        PlaySoundA((LPCSTR)sound, nullptr, SND_APPLICATION | SND_ASYNC | SND_NODEFAULT);
    });

    const auto registeredKeys = lua.getVector<int>((char*)"registeredKeys");
    const auto begin = registeredKeys.begin();
    const auto end = registeredKeys.end();

    for (;; Sleep(50))
    {
        for(const int key : registeredKeys)
        {
            if (GetAsyncKeyState(key) & 1)
            {
                lua.callFunction("handleKey", key);
            }
        }

        if (GetAsyncKeyState(VK_F9) & 1)
        {
            std::cout << "F9" << std::endl;
        }

        if (GetAsyncKeyState(KEY_Q) & 1)
        {
            break;
        }
    }

    return 0;
}

void loadLuaState(GameTrainer::mylib::LuaWrapper& lua)
{
#if DEBUG
    constexpr char* script = (char*)R"(
key_codes = {
	VK_F5 = 0x74,
	VK_F6 = 0x75,
	VK_F7 = 0x76
}
processName = 'KillingFloor.exe'
maxHealth = 100
registeredKeys = {
    key_codes.VK_F6,
    key_codes.VK_F7
}

function handleKey (key)
	if key == key_codes.VK_F6 then
		print('many many')
		playSound('sounds/money.wav')
	elseif key == key_codes.VK_F7 then
		print('off')
		playSound('sounds/off.wav')
	else
		print('unknown key')
	end
end
		)";
    lua.loadString(script);
#else
    lua.loadFile("scripts/KillingFloor.lua");
#endif
}
