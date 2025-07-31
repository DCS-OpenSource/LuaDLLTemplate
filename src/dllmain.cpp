#include <Windows.h>
#include <stdio.h>

extern "C" {
    #include "lua.h"
}

#include "template.h"  // defines tpl::l_template

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

// Lua module entry point, the name after "luaopen_" must equal the name of the dll file
extern "C" __declspec(dllexport) int luaopen_LuaPlugin(lua_State* L)
{
    return template_mod::l_template(L);
}
