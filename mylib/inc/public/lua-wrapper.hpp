#ifndef GAMETRAINER_LUA_WRAPPER_HPP
#define GAMETRAINER_LUA_WRAPPER_HPP

#include <iostream>
#include <vector>

#include <lua.hpp>

#include "lua-status.hpp"

namespace GameTrainer::mylib
{
    template<class T>
    LUA_STATUS setInteger(T& value, lua_State* LUA);

    template<class T>
    LUA_STATUS setString(T& value, lua_State* LUA);

    template<class T>
    bool setValue(T& value, lua_State* LUA, char* variableName = nullptr);

    template<class T>
    void setVector(std::vector<T>& vector, lua_State* LUA, char* variableName);

    void execute();

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

            return LUA_STATUS_HAS_NO_VALUE;
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

            return LUA_STATUS_HAS_NO_VALUE;
        }

        return LUA_STATUS_HAS_ANOTHER_TYPE;
    }

    template<class T>
    bool setValue(T& value, lua_State* LUA, char* variableName)
    {
        if (variableName) {
            lua_getglobal(LUA, variableName);
        }

        LUA_STATUS (*valueSetters[])(T&, lua_State*) = {
                setString,
                setInteger
        };

        for(const auto& setter : valueSetters)
        {
            switch (setter(value, LUA))
            {
                case LUA_STATUS_HAS_VALUE: return true;
                case LUA_STATUS_HAS_NO_VALUE: return false;
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

    class LuaWrapper
    {
    public:
        int method(const int x);

        LuaWrapper();

    private:
        int field;
    };

}

#endif //GAMETRAINER_LUA_WRAPPER_HPP
