-- Path to your DLL files folder
local dll_path = LockOn_Options.script_path.."LuaPluginTest/"

local function load_dll()
    package.cpath = package.cpath .. ";" .. dll_path .. "/?.dll"
    success, result = pcall(require, 'LuaPlugin') -- DLL files name
    if not success then
        print_message_to_user("Lua DLL template failed to load from: " .. dll_path)
    end
    return result
end

return load_dll()