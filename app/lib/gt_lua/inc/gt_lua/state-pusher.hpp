#ifndef GAMETRAINER_STATE_PUSHER_HPP
#define GAMETRAINER_STATE_PUSHER_HPP

#include <exception>

#include <lua.h>

namespace gt::lua
{
    namespace internal
    {
        template<class T>
        struct StatePusherInternal
        {
            static void push(lua_State *luaState, const T& arg)
            {
                throw std::exception();
            }
        };

        #define GENERATE_STATE_PUSHER(T, func)                      \
        template<>                                                  \
        struct StatePusherInternal<T>                               \
        {                                                           \
            static void push(lua_State* luaState, const T& arg)     \
            {                                                       \
                func(luaState, arg);                                \
            }                                                       \
        };                                                          \

        GENERATE_STATE_PUSHER(int, lua_pushinteger);

        GENERATE_STATE_PUSHER(bool, lua_pushboolean);
    }

    struct StatePusher
    {
        template<class T>
        static void push(lua_State* luaState, const T& arg)
        {
            internal::StatePusherInternal<T>::push(luaState, arg);
        }

        template<class T, class... Rest>
        static void push(lua_State* luaState, const T& arg, const Rest&... rest)
        {
            StatePusher::push(luaState, arg);
            StatePusher::push(luaState, rest...);
        }
    };
}

#endif //GAMETRAINER_STATE_PUSHER_HPP
