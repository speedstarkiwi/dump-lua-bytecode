//dont use luac if u have 1 braincell you should at least know some things dont exist
//assuming your using lua not LUAU
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

const char* scriptsource = "print('i use axon')";

int main() {
    lua_State* L = luaL_newstate();

    luaL_loadstring(L, scriptsource);//luau doesnt have this..use luau load or something

    size_t len;//size
    const char* bytecode = lua_dump(L, [](lua_State*, const void* p, size_t sz, void* ud) {//get bytecode
        *(std::string*)ud += std::string((const char*)p, sz);
        return 0;
    }, new std::string(""), &len);

    printf("your shitty bytecode ->\n\n");
    for (size_t i = 0; i < len; i++) {//return bytecode
        printf("%02X ", bytecode[i] & 0xFF);
    }
    printf("\n");

    delete (std::string*)lua_touserdata(L, lua_upvalueindex(1));
    lua_close(L);

    return 0;
}
