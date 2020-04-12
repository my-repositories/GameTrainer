#ifndef GAMETRAINER_ERROR_HANDLER_HPP
#define GAMETRAINER_ERROR_HANDLER_HPP

#include <iostream>

#include <lua.hpp>

namespace gt::lua
{
    int errorHandler(lua_State *state);
}

#endif //GAMETRAINER_ERROR_HANDLER_HPP
