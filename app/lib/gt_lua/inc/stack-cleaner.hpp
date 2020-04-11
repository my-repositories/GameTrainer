#ifndef GAMETRAINER_STACK_CLEANER_HPP
#define GAMETRAINER_STACK_CLEANER_HPP

#include <lua.h>

namespace GameTrainer::mylib::lua
{
    class LuaStackCleaner
    {
    public:
        explicit LuaStackCleaner(lua_State *state)
        {
            this->state = state;
            this->top = lua_gettop(this->state);
        }

        ~LuaStackCleaner()
        {
            lua_settop(this->state, this->top);
        }

    private:
        lua_State *state;
        int top;
    };
}
#endif //GAMETRAINER_STACK_CLEANER_HPP
