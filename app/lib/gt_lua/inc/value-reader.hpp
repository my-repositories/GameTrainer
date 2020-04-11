#ifndef GAMETRAINER_VALUE_READER_HPP
#define GAMETRAINER_VALUE_READER_HPP

#include <exception>
#include <optional>
#include <vector>

#include <lua.h>

#include <stack-cleaner.hpp>

namespace GameTrainer::mylib::lua
{
    struct ValueReader
    {
        template<class T>
        [[nodiscard]] static std::optional<T> readValue(lua_State* luaState, char* variableName = nullptr)
        {
            if (variableName)
            {
                lua_getglobal(luaState, variableName);
            }

            return ValueReaderInternal<T>::read(luaState);
        }

        template<class T>
        [[nodiscard]] static std::vector<T> readVector(lua_State* luaState, char* variableName)
        {
            LuaStackCleaner cleaner(luaState);

            lua_getglobal(luaState, variableName);
            std::vector<T> vector;

            for (LUA_NUMBER i = 1; true; ++i)
            {
                lua_pushnumber(luaState, i);
                lua_gettable(luaState, -2);

                auto item = ValueReader::readValue<T>(luaState);
                if (!item.has_value())
                {
                    break;
                }

                vector.push_back(*item);
                lua_pop(luaState, 1);
            }

            return vector;
        }

    private:
        template<class T>
        struct ValueReaderInternal
        {
            static auto read(lua_State *luaState)
            {
                throw std::exception("Invalid type for struct 'valueReader'");
            }
        };

        #define GENERATE_VALUE_READER(T, predicate, reader)         \
        template<>                                                  \
        struct ValueReaderInternal<T>                               \
        {                                                           \
            static auto read(lua_State* luaState)                   \
            {                                                       \
                std::optional<T> value;                             \
                                                                    \
                if (predicate(luaState, -1))                        \
                {                                                   \
                    value = (T)reader(luaState, -1);                \
                }                                                   \
                                                                    \
                return value;                                       \
            }                                                       \
        };                                                          \

        GENERATE_VALUE_READER(int, lua_isinteger, lua_tointeger);

        GENERATE_VALUE_READER(char*, lua_isstring, lua_tostring);
    };
}

#endif //GAMETRAINER_VALUE_READER_HPP
