#include "r_lua.h"
#include "iostream"

LuaScript::LuaScript(const std::string &filename)
{
    L = luaL_newstate();
    if (luaL_loadfile(L, filename.c_str()) || lua_pcall(L, 0, 0, 0))
    {
        std::cout << "Error: Script did not load (" << filename << ")" << std::endl;
        L = 0;
    }
}

LuaScript::~LuaScript()
{
    if(L) lua_close(L);
}

void LuaScript::PrintError(const std::string &variableName, const std::string &error)
{
    std::cout << "Error: Script did not get:'" << variableName << "' :: " << error << std::endl;
}

bool LuaScript::lua_gettostack(const std::string &variableName)
{
    level = 0;
    std::string var = "";
    for(auto &c : variableName)
    {
        if(c == '.')
        {
            if (level == 0)
            {
                lua_getglobal(L, var.c_str());
            }else{
                lua_getfield(L, -1, var.c_str());
            }
            
            if (lua_isnil(L, -1))
            {
                PrintError(variableName, var + " is not defined.");
                return false;
            }else
            {
                var = "";
                level++;
            }
        }else
        {
            var += c;
        }
    }
    if (level == 0) {
        lua_getglobal(L, var.c_str());
    }else
    {
        lua_getfield(L, -1, var.c_str());
    }
    if(lua_isnil(L, -1))
    {
        PrintError(variableName, var + " is not defined.");
        return false;
    }
    return true;
}
