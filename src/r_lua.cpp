#include "r_lua.h"
#include "iostream"

void LuaScript::ClearStack()
{
    int n = lua_gettop(L);
    lua_pop(L, n);
}

bool LuaScript::GetToStack(const std::string &variableName)
{
    _level = 0;
    std::string var = "";
    for(auto &c : variableName)
    {
        if(c == '.')
        {
            if (_level == 0)
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
                _level++;
            }
        }else
        {
            var += c;
        }
    }
    if (_level == 0) {
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

void LuaScript::PrintError(const std::string &variableName, const std::string &error)
{
    std::cout << "Error: Script did not get:'" << variableName << "' :: " << error << std::endl;
}

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


