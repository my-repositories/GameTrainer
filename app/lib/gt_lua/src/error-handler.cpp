#include <iostream>

#include <gt_lua/error-handler.hpp>

namespace gt::lua {
int errorHandler(lua_State *state) {
    const char *message = lua_tostring(state, 1);
    std::cout << "Error: " << message << std::endl;

    lua_getglobal(state, "debug");
    lua_getfield(state, -1, "traceback");

    if (lua_pcall(state, 0, 1, 0)) {
        const char *err = lua_tostring(state, -1);
        std::cout << "Error in debug.traceback() call: " << err << std::endl;
    } else {
        const char *err = lua_tostring(state, -1);
        std::cout << "C++ stack traceback: " << err << std::endl;
    }

    return 1;
}
} // namespace gt::lua
