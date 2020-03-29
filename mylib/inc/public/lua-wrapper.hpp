#ifndef GAMETRAINER_LUA_WRAPPER_HPP
#define GAMETRAINER_LUA_WRAPPER_HPP

#include <iostream>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>

#include <lua.hpp>

#include <lua-stack-cleaner.hpp>

namespace GameTrainer::mylib
{
    typedef std::optional<int> lua_int;
    typedef std::optional<char*> lua_string;
    typedef
    std::variant<
            std::nullopt_t,
            lua_int,
            lua_string
    >
    lua_variant;

    class LuaWrapper
    {
    public:
        LuaWrapper();

        explicit LuaWrapper(lua_State* state);

        ~LuaWrapper();

        inline void loadFile(const char* path) const { luaL_dofile(this->state, path); }

        inline void loadString(const char* script) const { luaL_dostring(this->state, script); }

        void callFunction(const char* name, int arg) const;

        void registerFunction(const char* name, void(*callback)(const char*)) const;

        template<class T>
        std::optional<T> getValue(char* variableName = nullptr) const
        {
            if (variableName)
            {
                lua_getglobal(this->state, variableName);
            }

            auto variant = this->getVariant<T>();
            if (!variant.index())
            {
                return std::nullopt;
            }

            return std::get<std::optional<T>>(variant);
        }

        template<class T>
        std::vector<T> getVector(char* variableName) const
        {
            LuaStackCleaner cleaner(this->state);

            lua_getglobal(this->state, variableName);
            std::vector<T> vector;

            for (LUA_NUMBER i = 1; true; ++i)
            {
                lua_pushnumber(this->state, i);
                lua_gettable(this->state, -2);

                auto item = getValue<T>();
                if (!item.has_value())
                {
                    break;
                }

                vector.push_back(*item);
                lua_pop(this->state, 1);
            }

            return vector;
        }

    private:
        lua_State* state;

        static int errorHandler(lua_State* state);

        [[nodiscard]] lua_int getInteger() const;

        [[nodiscard]] lua_string getString() const;

        template<class T>
        [[nodiscard]] lua_variant getVariant() const
        {
            if constexpr (std::is_same<T, int>::value)
            {
                return this->getInteger();
            }

            if constexpr (std::is_same<T, char*>::value)
            {
                return this->getString();
            }

            return std::nullopt;
        }
    };
}

#endif //GAMETRAINER_LUA_WRAPPER_HPP
