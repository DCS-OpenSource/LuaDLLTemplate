#pragma once
#include "template.h"

extern "C" {
    #include "lua.h"
    #include "lauxlib.h"
}

#include <string>


#define REGISTER_FUNCTION(fn) { #fn, fn }

namespace template_mod {

// Simple add
int Add(lua_State* L) {
    int a = luaL_checkinteger(L, 1);
    int b = luaL_checkinteger(L, 2);
    lua_pushinteger(L, a + b);
    return 1;
}

// Example table
int ExampleTable(lua_State* L) {
    lua_newtable(L);
    lua_pushinteger(L, 1); lua_pushinteger(L, 123); lua_settable(L, -3);
    return 1;
}

// Register your functions
int l_template(lua_State* L) {
    lua_newtable(L);
    static const luaL_Reg funcs[] = {
        REGISTER_FUNCTION(Add),
        REGISTER_FUNCTION(ExampleTable),
        { nullptr, nullptr }
    };
#if LUA_VERSION_NUM >= 502
    luaL_setfuncs(L, funcs, 0);
#else
    luaL_register(L, nullptr, funcs);
#endif
    lua_pushstring(L, "template_mod");
    lua_setfield(L, -2, "__name");
    return 1;
}

} // namespace template_mod
