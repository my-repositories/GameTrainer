#ifndef GAMETRAINER_LUA_STACK_CLEANER_HPP
#define GAMETRAINER_LUA_STACK_CLEANER_HPP

#include <lua.h>

class LuaStackCleaner
{
public:
    LuaStackCleaner(lua_State* state)
    {
        this->state = state;
        this->top = lua_gettop(this->state);
    }

    ~LuaStackCleaner()
    {
        lua_settop(this->state, this->top);
    }

private:
    lua_State* state;
    int top;
};

#endif //GAMETRAINER_LUA_STACK_CLEANER_HPP
