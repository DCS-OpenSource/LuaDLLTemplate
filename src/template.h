#pragma once

struct lua_State;

namespace template_mod
{
    // Registration function for the Lua module
    extern int l_template(lua_State* L);
}
