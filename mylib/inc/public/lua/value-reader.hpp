#ifndef GAMETRAINER_VALUE_READER_HPP
#define GAMETRAINER_VALUE_READER_HPP

#include <exception>
#include <optional>

#include <lua.h>

namespace GameTrainer::mylib::lua
{
    template<typename T>
    struct ValueReader
    {
        static auto read(lua_State *luaState)
        {
            throw std::exception("Invalid type for struct 'valueReader'");
        }
    };

    #define GENERATE_VALUE_READER(T, predicate, getter) \
    template<>                                      \
    struct ValueReader<T>                           \
    {                                               \
        static auto read(lua_State* luaState)       \
        {                                           \
            std::optional<T> value;                 \
                                                    \
            if (predicate(luaState, -1))            \
            {                                       \
                value = (T)getter(luaState, -1);    \
            }                                       \
                                                    \
            return value;                           \
        }                                           \
    };                                              \

    GENERATE_VALUE_READER(int, lua_isinteger, lua_tointeger);

    GENERATE_VALUE_READER(char*, lua_isstring, lua_tostring);
}

#endif //GAMETRAINER_VALUE_READER_HPP
