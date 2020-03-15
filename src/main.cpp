#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

#include <gg.h>
#include <lua.hpp>

#define KEY_Q 0x51

/* the Lua interpreter */
lua_State* L;

int handleKey(int key)
{
    lua_getglobal(L, "handleKey");
    lua_pushnumber(L, key);
    lua_call(L, 1, 0);

    return 0;
}

std::vector<int> getRegisteredKeys()
{
    lua_getglobal(L, "keys");
    lua_getfield(L, -1, "size");
    int size = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_pushliteral(L, "registered");
    lua_gettable(L, -2);

    std::vector<int> registeredKeys;
    for (LUA_NUMBER i = 0; i < size; ++i)
    {
        lua_pushnumber(L, i + 1);
        lua_gettable(L, -2);
        registeredKeys.push_back(lua_tointeger(L, -1));
        lua_pop(L, 1);
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

int main(int argc, char* argv[])
{
    L = lua_open();
    luaL_openlibs(L);
    lua_register(L, "writeMemory", writeMemory);
    luaL_dofile(L, "script.lua");

    const auto registeredKeys = getRegisteredKeys();
    const auto begin = registeredKeys.begin();
    const auto end = registeredKeys.end();

    for (;; Sleep(50)) {
        std::for_each(begin, end, checkKeyState);

        if (GetAsyncKeyState(KEY_Q) & 1)
        {
            break;
        }
    }

    lua_close(L);

    std::cout << wp() << std::endl;

    return 0;
}
