#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

#include <gg.hpp>
#include <lua.hpp>

#define KEY_Q 0x51

/* the Lua interpreter */
lua_State* LUA;

int handleKey(int key)
{
    lua_getglobal(LUA, "handleKey");
    lua_pushnumber(LUA, key);
    lua_call(LUA, 1, 0);

    return 0;
}

std::vector<int> getRegisteredKeys()
{
    lua_getglobal(LUA, "keys");
    lua_getfield(LUA, -1, "size");
    int size = lua_tointeger(LUA, -1);
    lua_pop(LUA, 1);
    std::cout << "size=" << size << std::endl;

    lua_pushliteral(LUA, "registered");
    lua_gettable(LUA, -2);

    std::vector<int> registeredKeys;
    for (LUA_NUMBER i = 0; i < size; ++i)
    {
        lua_pushnumber(LUA, i + 1);
        lua_gettable(LUA, -2);
        registeredKeys.push_back(lua_tointeger(LUA, -1));
        lua_pop(LUA, 1);
    }

    return registeredKeys;
}

void checkKeyState(const int key)
{
    if (GetAsyncKeyState(key) & 1)
    {
        handleKey(key);
    }
}

int writeMemory(lua_State* L)
{
    int argc = lua_gettop(L);

    if (argc >= 1)
    {
        if (lua_isstring(L, -argc))
        {
            std::cout << lua_tostring(L, -argc) << std::endl;
        }
    }

    return 0;
}

int playSound(lua_State* LUA)
{
    int argc = lua_gettop(LUA);

    if (argc >= 1)
    {
        if (lua_isstring(LUA, -argc))
        {
            const char* sound = lua_tostring(LUA, -argc);
            PlaySoundA((LPCSTR)sound, NULL, SND_APPLICATION | SND_ASYNC | SND_NODEFAULT);
        }
    }

    return 0;
}

int main(int argc, char* argv[])
{
    std::cout << "Version:" << MY_VERSION << std::endl;
    std::cout << wp() << std::endl;

    {
        lua_State* L = luaL_newstate();
        luaL_dostring(L, "x = 42");
        lua_getglobal(L, "x");
        lua_Number x = lua_tonumber(L, 1);
        std::cout << (int)x << std::endl;
        lua_close(L);
    }

    {
        lua_State* L = luaL_newstate();
        luaL_dofile(L, "a.lua");
        lua_getglobal(L, "x");
        lua_Number x = lua_tonumber(L, 1);
        std::cout << (int)x << std::endl;
        lua_close(L);
    }

    LUA = luaL_newstate();
    luaL_openlibs(LUA);
    lua_register(LUA, "playSound", playSound);
    lua_register(LUA, "writeMemory", writeMemory);
    luaL_dofile(LUA, "scripts/KillingFloor.lua");

    const auto registeredKeys = getRegisteredKeys();
    const auto begin = registeredKeys.begin();
    const auto end = registeredKeys.end();

    for (;; Sleep(50)) {
        std::for_each(begin, end, checkKeyState);

        if (GetAsyncKeyState(VK_F8) & 1)
        {
            std::cout << "f8" << std::endl;
        }

        if (GetAsyncKeyState(KEY_Q) & 1)
        {
            break;
        }
    }

    lua_close(LUA);

    std::cout << wp() << std::endl;

    return 0;
}
