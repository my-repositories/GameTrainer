#ifndef GAMETRAINER_STATE_PUSHER_HPP
#define GAMETRAINER_STATE_PUSHER_HPP

#include <exception>

#include <lua.h>

namespace GameTrainer::mylib::lua
{
    template<typename T>
    struct StatePusher
    {
        static void push(lua_State *luaState, const T& arg)
        {
            throw std::exception("Invalid type for struct 'StatePusher'");
        }
    };

#define GENERATE_STATE_PUSHER(T, func)                          \
    template<>                                                  \
    struct StatePusher<T>                                       \
    {                                                           \
        static void push(lua_State* luaState, const T& arg)     \
        {                                                       \
            func(luaState, arg);                                \
        }                                                       \
    };                                                          \

    GENERATE_STATE_PUSHER(int, lua_pushinteger);

    GENERATE_STATE_PUSHER(bool, lua_pushboolean);
}

#endif //GAMETRAINER_STATE_PUSHER_HPP
