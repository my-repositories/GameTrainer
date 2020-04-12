#include <gt_lua/wrapper.hpp>

namespace gt::lua
{
    LuaWrapper::LuaWrapper()
        : LuaWrapper(luaL_newstate())
        {}

    LuaWrapper::LuaWrapper(lua_State *state)
    {
        this->state = state;
        luaL_openlibs(this->state);
    }

    LuaWrapper::~LuaWrapper()
    {
        lua_close(this->state);
    }

    void LuaWrapper::registerFunction(const char *name, void (*callback)(xml::CheatEntry*, float)) const
    {
        lua_pushlightuserdata(this->state, (void*)callback);
        lua_pushcclosure(this->state, [](lua_State* luaState) -> int
        {
            constexpr const int callBackIndex = lua_upvalueindex(1);
            if (lua_gettop(luaState) != 2
                || !lua_isuserdata(luaState, -2)
                || !lua_islightuserdata(luaState, callBackIndex)
            )
            {
                return 0;
            }

            auto func = (void(*)(xml::CheatEntry*, float))lua_touserdata(luaState, callBackIndex);
            auto data = (xml::CheatEntry*)lua_touserdata(luaState, -2);
            float value = 0;

            if (lua_isnumber(luaState, -1))
            {
                value = (float) lua_tonumber(luaState, -1);
            }

            func(data, value);

            return 0;
        }, 1);

        lua_setglobal(this->state, name);
    }

    void LuaWrapper::registerFunction(const char *name, void (*callback)(const char*)) const
    {
        lua_pushlightuserdata(this->state, (void*)callback);
        lua_pushcclosure(this->state, [](lua_State* luaState) -> int
        {
            if (lua_gettop(luaState) == 1 && lua_isstring(luaState, -1))
            {
                constexpr const int userDataIndex = lua_upvalueindex(1);

                if (lua_islightuserdata(luaState, userDataIndex))
                {
                    auto func = (void(*)(const char*))lua_touserdata(luaState, userDataIndex);
                    const char* data = lua_tostring(luaState, -1);
                    func(data);
                }
            }

            return 0;
        }, 1);

        lua_setglobal(this->state, name);
    }

    void LuaWrapper::registerFunction(const char *name, int (*callback)(lua_State*, const char*)) const
    {
        lua_pushlightuserdata(this->state, (void*)callback);
        lua_pushcclosure(this->state, [](lua_State* luaState) -> int
        {
            constexpr const int userDataIndex = lua_upvalueindex(1);

            if (lua_islightuserdata(luaState, userDataIndex))
            {
                auto func = (int(*)(lua_State*, const char*))lua_touserdata(luaState, userDataIndex);
                const char* data = lua_tostring(luaState, -1);
                func(luaState, data);
            }

            return 1;
        }, 1);

        lua_setglobal(this->state, name);
    }
}
