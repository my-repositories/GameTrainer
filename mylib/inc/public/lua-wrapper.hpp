#ifndef GAMETRAINER_LUA_WRAPPER_HPP
#define GAMETRAINER_LUA_WRAPPER_HPP

#include <iostream>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>

#include <lua.hpp>

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
        LuaWrapper()
        : LuaWrapper(luaL_newstate()) {}

        explicit LuaWrapper(lua_State* state)
        {
            this->state = state;
            luaL_openlibs(this->state);
        }

        ~LuaWrapper()
        {
            lua_close(this->state);
        }

        inline void loadFile(const char* path) const
        {
            luaL_dofile(this->state, path);
        }
        inline void loadString(const char* script) const
        {
            luaL_dostring(this->state, script);
        }

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

        void callFunction(const char* name, const int arg) const
        {
            lua_getglobal(this->state, name);
            if (!lua_isfunction(this->state, -1))
            {
                std::cout << "function \"" << name << "\"" << " was not found." << std::endl;

                return;
            }

            lua_pushinteger(this->state, arg);
            lua_call(this->state, 1, 0);
        }

        void registerFunction(const char* name, void(*callback)(const char*)) const
        {
            lua_pushlightuserdata(state, (void*)callback);
            lua_pushcclosure(state, [](lua_State* state) -> int
            {
                if (lua_gettop(state) == 1 && lua_isstring(state, -1))
                {
                    constexpr const int userDataIndex = lua_upvalueindex(1);

                    if (lua_isuserdata(state, userDataIndex))
                    {
                        auto func = (void(*)(const char*))lua_touserdata(state, userDataIndex);
                        func(lua_tostring(state, -1));
                    }
                }

                return 0;
            }, 1);

            lua_setglobal(state, name);
        }

    private:
        lua_State* state;

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

        [[nodiscard]] lua_int getInteger() const
        {
            if (lua_isinteger(this->state, -1))
            {
                return (int) lua_tointeger(this->state, -1);
            }

            return std::nullopt;
        }

        [[nodiscard]] lua_string getString() const
        {
            if (lua_isstring(this->state, -1))
            {
                return (char*) lua_tostring(this->state, -1);
            }

            return std::nullopt;
        }
    };
}

#endif //GAMETRAINER_LUA_WRAPPER_HPP
