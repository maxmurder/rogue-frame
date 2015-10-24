#ifndef R_LUA_H
#define R_LUA_H

#include<string>
#include<vector>
#include<iostream>

extern "C" {
# include "lua5.2/lua.h"
# include "lua5.2/lauxlib.h"
# include "lua5.2/lualib.h"
}

class LuaScript {
    public:
    LuaScript(const std::string &filename);
    ~LuaScript();
    void PrintError(const std::string &variableName, const std::string &error);
    
    template<typename T>
    T get(const std::string &variableName)
    {
        if (!L) 
        {
            PrintError(variableName, "Script not loaded.");
            return lua_getdefault<T>();
        }
        
        T result;
        if(lua_gettostack(variableName))
        {
            result = lua_get<T>(variableName);
        }else 
        {
            result = lua_getdefault<T>();
        }
        
        lua_pop(L, level + 1);
        return result;
    }
   
    bool lua_gettostack(const std::string &variableName);
   
    template<typename T>
    T lua_get(const std::string &variableName)
    {
        return 0;
    }
    
    template<typename T>
    T lua_getdefault()
    {
        return 0;
    }
    
    private:
    lua_State* L;
    std::string filename;
    int level; 
};

template<>
inline std::string LuaScript::lua_getdefault<std::string>()
{
    return "null";
}

template<>
inline bool LuaScript::lua_get<bool>(const std::string &variableName)
{
    return (bool)lua_toboolean(L, -1);
}

template<>
inline float LuaScript::lua_get<float>(const std::string &variableName)
{
    if(!lua_isnumber(L, -1))
    {
        PrintError(variableName, "Not a number");
    }
    return (float)lua_tonumber(L, -1);
}

template<>
inline std::string LuaScript::lua_get<std::string>(const std::string &variableName)
{
    std::string s = "null";
    if( lua_isstring(L, -1))
    {
        s = std::string(lua_tostring(L, -1));
    }else
    {
        PrintError(variableName, "Not a string");
    }
    return s;
}

#endif
