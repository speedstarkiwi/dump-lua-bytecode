extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

int main() {
    // Create a new Lua state
    lua_State* L = luaL_newstate();

    // Load the Lua script
    luaL_loadstring(L, "print('Hello, world!')");

    // Dump the Lua script to bytecode
    size_t len;
    const char* bytecode = lua_dump(L, [](lua_State*, const void* p, size_t sz, void* ud) {
        *(std::string*)ud += std::string((const char*)p, sz);
        return 0;
    }, new std::string(""), &len);

    // Print the bytecode
    for (size_t i = 0; i < len; i++) {
        printf("%02X ", bytecode[i] & 0xFF);
    }
    printf("\n");

    // Clean up
    delete (std::string*)lua_touserdata(L, lua_upvalueindex(1));
    lua_close(L);

    return 0;
}
