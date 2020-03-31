#include <lua-wrapper.hpp>

namespace GameTrainer::mylib
{
    LuaWrapper::LuaWrapper()
        : LuaWrapper(luaL_newstate()) {}

    LuaWrapper::LuaWrapper(lua_State *state)
    {
        this->state = state;
        luaL_openlibs(this->state);
    }

    LuaWrapper::~LuaWrapper()
    {
        lua_close(this->state);
    }

    void LuaWrapper::registerFunction(const char *name, void (*callback)(const char *)) const
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
                    func(lua_tostring(luaState, -1));
                }
            }

            return 0;
        }, 1);

        lua_setglobal(this->state, name);
    }

    lua_int LuaWrapper::getInteger() const
    {
        if (lua_isinteger(this->state, -1))
        {
            return (int) lua_tointeger(this->state, -1);
        }

        return std::nullopt;
    }

    lua_string LuaWrapper::getString() const
    {
        if (lua_isstring(this->state, -1))
        {
            return (char*) lua_tostring(this->state, -1);
        }

        return std::nullopt;
    }

    int LuaWrapper::errorHandler(lua_State *state) {
        const char* message = lua_tostring(state, 1);
        std::cout << "Error: " << message << std::endl;

        lua_getglobal(state, "debug");
        lua_getfield(state, -1, "traceback");

        if(lua_pcall(state, 0, 1, 0))
        {
            const char* err = lua_tostring(state, -1);
            std::cout << "Error in debug.traceback() call: " << err << std::endl;
        }
        else
        {
            const char* err = lua_tostring(state, -1);
            std::cout << "C++ stack traceback: " << err << std::endl;
        }

        return 1;
    }
}
