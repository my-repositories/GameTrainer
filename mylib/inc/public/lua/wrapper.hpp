#ifndef GAMETRAINER_WRAPPER_HPP
#define GAMETRAINER_WRAPPER_HPP

#include <iostream>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>
#include <Windows.h>

#include <lua.hpp>

#include <lua/stack-cleaner.hpp>
#include <xml/table-reader.hpp>

namespace GameTrainer::mylib::lua
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

        template<class... Args>
        void callFunction(const char *name, const Args&... args) const
        {
            LuaStackCleaner cleaner(this->state);

            lua_pushcfunction(this->state, &LuaWrapper::errorHandler);
            lua_getglobal(this->state, name);
            if (!lua_isfunction(this->state, -1))
            {
                std::cout << "function '" << name << "'" << " was not found." << std::endl;

                return;
            }

            this->pushToState(args...);
            const int argsCount = sizeof...(args);

            lua_pcall(this->state, argsCount, 0, -(2 + argsCount));
        }

        template<class T>
        void pushToState(const T& arg) const
        {
            if constexpr (std::is_same<T, int>::value)
            {
                lua_pushinteger(this->state, arg);
            }
            else if constexpr (std::is_same<T, bool>::value)
            {
                lua_pushboolean(this->state, arg);
            }
        }

        template<
            class FIRST,
            class... REST
        >
        void pushToState(const FIRST& first, const REST&... rest) const
        {
            pushToState(first);
            pushToState(rest...);
        }

        void registerFunction(const char* name, void(*callback)(xml::CheatEntry*, float)) const;

        void registerFunction(const char* name, void(*callback)(const char*)) const;

        void registerFunction(const char* name, int(*callback)(lua_State*, const char*)) const;

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

        static int createUserData(lua_State* luaState, const char* fileName)
        {
            auto entries = xml::TableReader::read(fileName);

            lua_newtable(luaState);

            for (auto& entry : entries)
            {
                lua_pushstring(luaState, entry.description);

                auto field = (xml::CheatEntry *) lua_newuserdata(luaState, sizeof(xml::CheatEntry));

                field->size = entry.size;
                field->offsetsCount = entry.offsetsCount;

                constexpr const size_t offsetsSize = sizeof(entry.offsets);
                memcpy_s(field->offsets, offsetsSize, entry.offsets, offsetsSize);

                field->address = entry.address;

                constexpr const size_t moduleCount = sizeof(field->module)/sizeof(field->module[0]);
                strncpy_s(field->module, entry.module, moduleCount);

                field->description[0] = '\0';
                field->variableType[0] = '\0';

                lua_settable(luaState, -3);
            }

            return 1;
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

#endif //GAMETRAINER_WRAPPER_HPP
