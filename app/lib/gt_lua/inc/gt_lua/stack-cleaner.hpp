#ifndef GAMETRAINER_STACK_CLEANER_HPP
#define GAMETRAINER_STACK_CLEANER_HPP

#include <lua.h>

namespace gt::lua {
class LuaStackCleaner {
  public:
    explicit LuaStackCleaner(lua_State *state) {
        this->state = state;
        this->top = lua_gettop(this->state);
    }

    ~LuaStackCleaner() { lua_settop(this->state, this->top); }

  private:
    lua_State *state;
    int top;
};
} // namespace gt::lua
#endif // GAMETRAINER_STACK_CLEANER_HPP
