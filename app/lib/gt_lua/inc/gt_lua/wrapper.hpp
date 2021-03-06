#ifndef GAMETRAINER_WRAPPER_HPP
#define GAMETRAINER_WRAPPER_HPP

#include <cstring>
#include <iostream>
#include <optional>
#include <vector>

#include <lua.hpp>

#include <gt_lua/error-handler.hpp>
#include <gt_lua/stack-cleaner.hpp>
#include <gt_lua/state-pusher.hpp>
#include <gt_lua/value-reader.hpp>
#include <gt_xml/table-reader.hpp>

namespace gt::lua {
class LuaWrapper {
  public:
    LuaWrapper();

    explicit LuaWrapper(lua_State *state);

    ~LuaWrapper();

    inline void loadFile(const char *path) const {
        luaL_dofile(this->state, path);
    }

    inline void loadString(const char *script) const {
        luaL_dostring(this->state, script);
    }

    template <class... Args>
    void callFunction(const char *name, const Args &... args) const {
        LuaStackCleaner cleaner(this->state);

        lua_pushcfunction(this->state, errorHandler);
        lua_getglobal(this->state, name);
        if (!lua_isfunction(this->state, -1)) {
            std::cout << "function '" << name << "'"
                      << " was not found." << std::endl;

            return;
        }

        StatePusher::push(this->state, args...);
        const int argsCount = sizeof...(args);

        lua_pcall(this->state, argsCount, 0, -(2 + argsCount));
    }

    void registerFunction(const char *name,
                          void (*callback)(xml::CheatEntry *, float)) const;

    void registerFunction(const char *name,
                          void (*callback)(const char *)) const;

    void registerFunction(const char *name,
                          int (*callback)(lua_State *, const char *)) const;

    template <class T>
    [[nodiscard]] std::optional<T>
    getValue(char *variableName = nullptr) const {
        return ValueReader::readValue<T>(this->state, variableName);
    }

    template <class T>
    [[nodiscard]] std::vector<T> getVector(char *variableName) const {
        return ValueReader::readVector<T>(this->state, variableName);
    }

    [[nodiscard]] static int createUserData(lua_State *luaState,
                                            const char *fileName) {
        auto entries = xml::TableReader::read(fileName);

        lua_newtable(luaState);

        for (auto &entry : entries) {
            lua_pushstring(luaState, entry.description);

            auto field = (xml::CheatEntry *)lua_newuserdata(
                luaState, sizeof(xml::CheatEntry));

            field->size = entry.size;
            field->offsetsCount = entry.offsetsCount;

            constexpr const size_t offsetsSize = sizeof(entry.offsets);

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            memcpy_s(field->offsets, offsetsSize, entry.offsets, offsetsSize);
#else
            memcpy(field->offsets, entry.offsets, offsetsSize);
#endif

            field->address = entry.address;

            constexpr const size_t moduleCount =
                sizeof(field->module) / sizeof(field->module[0]);

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)
            strncpy_s(field->module, entry.module, moduleCount);
#else
            strncpy(field->module, entry.module, moduleCount);
#endif

            field->description[0] = '\0';
            field->variableType[0] = '\0';

            lua_settable(luaState, -3);
        }

        return 1;
    }

  private:
    lua_State *state;
};
} // namespace gt::lua

#endif // GAMETRAINER_WRAPPER_HPP
