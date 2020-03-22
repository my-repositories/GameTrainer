#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <type_traits>
//#include <optional>
//#include <variant>

#include <gg.hpp>
#include <lua.hpp>
#include <config.hpp>
#include <game.hpp>

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

//std::optional<int> getInt(lua_State* LUA, char* variableName)
//{
//    lua_getglobal(LUA, variableName);
//    if (lua_isinteger(LUA, -1))
//    {
//        int number = (int) lua_tointeger(LUA, -1);
//        return std::make_optional(number);
//    }
//
//    return std::nullopt;
//}
//
//std::optional<char*> getString(lua_State* LUA, char* variableName)
//{
//    lua_getglobal(LUA, variableName);
//    if (lua_isstring(LUA, -1))
//    {
//        char* str = (char*) lua_tostring(LUA, -1);
//        return std::make_optional(str);
//    }
//
//    return std::nullopt;
//}
//
//std::vector<int> getVectorOfInt(lua_State* LUA, char* variableName)
//{
//    lua_getglobal(LUA, "registeredKeys");
//
//    std::vector<int> registeredKeys;
//    for (LUA_NUMBER i = 1; true; ++i)
//    {
//        lua_pushnumber(LUA, i);
//        lua_gettable(LUA, -2);
//
//        if (!lua_isinteger(LUA, -1))
//        {
//            break;
//        }
//
//        registeredKeys.push_back(lua_tointeger(LUA, -1));
//        lua_pop(LUA, 1);
//    }
//
//    return registeredKeys;
//}

enum LUA_STATUS {
    LUA_STATUS_HAS_VALUE,
    LUA_STATUS_HAS_NOT_VALUE,
    LUA_STATUS_HAS_ANOTHER_TYPE
};

template<class T>
LUA_STATUS setInteger(T& value, lua_State* LUA)
{
    if (std::is_same<T, int>::value)
    {
        if (lua_isinteger(LUA, -1))
        {
            value = (T) lua_tointeger(LUA, -1);
            return LUA_STATUS_HAS_VALUE;
        }

        return LUA_STATUS_HAS_NOT_VALUE;
    }

    return LUA_STATUS_HAS_ANOTHER_TYPE;
}

template<class T>
LUA_STATUS setString(T& value, lua_State* LUA)
{
    if (std::is_same<T, char*>::value)
    {
        if (lua_isstring(LUA, -1))
        {
            value = (T) lua_tostring(LUA, -1);
            return LUA_STATUS_HAS_VALUE;
        }

        return LUA_STATUS_HAS_NOT_VALUE;
    }

    return LUA_STATUS_HAS_ANOTHER_TYPE;
}

template <typename T, size_t N>
size_t sizeof_array(T (&)[N]){
    return N;
}

template<class T>
bool setValue(T& value, lua_State* LUA, char* variableName = nullptr)
{
    if (variableName) {
        lua_getglobal(LUA, variableName);
    }

    LUA_STATUS (*setters[])(T&, lua_State*) = {
        setString,
        setInteger
    };

    for (int i = sizeof_array(setters) - 1; i >= 0; --i)
    {
        switch (setters[i](value, LUA))
        {
            case LUA_STATUS_HAS_VALUE: return true;
            case LUA_STATUS_HAS_NOT_VALUE: return false;
            case LUA_STATUS_HAS_ANOTHER_TYPE: break;
            default: break;
        }
    }

    return false;
}

template<class T>
void setVector(std::vector<T>& vector, lua_State* LUA, char* variableName)
{
    lua_getglobal(LUA, variableName);

    for (LUA_NUMBER i = 1; true; ++i)
    {
        lua_pushnumber(LUA, i);
        lua_gettable(LUA, -2);

        T item;
        if (!setValue(item, LUA))
        {
            break;
        }

        vector.push_back(item);
        lua_pop(LUA, 1);
    }
}

template<class T>
std::vector<T> getField(lua_State* LUA, const std::string& path)
{
    std::cout << "same int:" << (int)std::is_same<T, int>::value << std::endl;
    std::cout << "same char*:" << (int)std::is_same<T, char*>::value << std::endl;
    std::cout << "same string:" << (int)std::is_same<T, std::string>::value << std::endl;

    lua_getglobal(LUA, "keys");
    lua_pushliteral(LUA, "registered");
    lua_gettable(LUA, -2);

    std::vector<T> registeredKeys;
    for (LUA_NUMBER i = 0; true; ++i)
    {
        lua_pushnumber(LUA, i + 1);
        lua_gettable(LUA, -2);

        if (lua_isinteger(LUA, -1))
        {
//            registeredKeys.push_back(lua_tointeger(LUA, -1));
            lua_pop(LUA, 1);
        }
        else
        {
            break;
        }
    }

    return registeredKeys;
}

int main(int argc, char* argv[])
{
    {
        lua_State* L = luaL_newstate();
        luaL_dostring(L, "processName = 'KillingFloor.exe'\n"
                           "maxHealth = 100\n"
                           "keys = {}\n"
                           "keys.size = 2\n"
                           "keys.registered = {\n"
                           "77,\n"
                           "13\n"
                           "}\n"
                           "perks = { 'bers', 'medic' }\n"
                           "registeredKeys = {\n"
                           "    87,\n"
                           "    69\n"
                           "}");

//        constexpr char* LUA_FILE = R"(
//		x = { 42, 15 }
//		)";
//        luaL_dostring(L, LUA_FILE);
//        lua_getglobal(L, "x");
//        lua_pushnumber(L, 1);
//        lua_gettable(L, -2);
//        int f = lua_tonumber(L, -1);
//        printf("f = %s\n", f);
//
//        lua_getglobal(L, "x");
//        lua_getfield(L, -1, "ian");
//        const char* ianIs = lua_tostring(L, -1);
//        printf("ianIs = %s\n", ianIs);

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

//        auto registeredKeys = getVectorOfInt(L, "registeredKeys");
//        for (int i = 0; i < registeredKeys.size(); ++i)
//        {
//            std::cout << i << ": " << registeredKeys[i] << std::endl;
//        }


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

//        auto processName = getString(L, "processName");
//        if (processName)
//        {
//            std::cout << *processName << std::endl;
//            std::cout << *processName << std::endl;
//            std::cout << *processName << std::endl;
//        }

//        auto maxHealth = getInt(L, "maxHealth");
//        if (maxHealth)
//        {
//            std::cout << *maxHealth << std::endl;
//            std::cout << *maxHealth << std::endl;
//            std::cout << *maxHealth << std::endl;
//            std::cout << *maxHealth << std::endl;
//        }

        lua_close(L);
    }

    return 0;

    {
        lua_State* LUA = luaL_newstate();
        luaL_dostring(LUA, "keys = {}\n"
                           "keys.registered = {\n"
                           "\t42,\n"
                           "\t55,\n"
                           "\t72\n"
                           "}");

        std::vector<int> registeredKeys = getField<int>(LUA, "");
        std::vector<char*> registeredKeys2 = getField<char*>(LUA, "");
        std::vector<std::string> registeredKeys3 = getField<std::string>(LUA, "");

        for (int i = 0; i < registeredKeys.size(); ++i)
        {
            std::cout << "i: " << registeredKeys[i] << std::endl;
        }

        lua_close(LUA);
    }

    return 0;

    Config cfg;
    std::cout << cfg.method(1) << std::endl;
    std::cout << cfg.method(3) << std::endl;
    std::cout << cfg.method(2) << std::endl;
    Game game;
    std::cout << game.method(1) << std::endl;
    std::cout << game.method(3) << std::endl;
    std::cout << game.method(2) << std::endl;
    std::cout << "Version:" << MY_PROJECT_VERSION << std::endl;
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
