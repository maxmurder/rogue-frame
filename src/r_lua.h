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
    LuaScript(const std::string &_filename);
    ~LuaScript();
    void PrintError(const std::string &variableName, const std::string &error);
    
    void ClearStack();
    
    template<typename T>
    T Get(const std::string &variableName)
    {
        if (!L) 
        {
            PrintError(variableName, "Script not loaded.");
            return Lua_GetDefault<T>();
        }
        
        T result;
        if(GetToStack(variableName))
        {
            result = Lua_Get<T>(variableName);
        }else 
        {
            result = Lua_GetDefault<T>();
        }
        
        lua_pop(L, _level + 1);
        return result;
    }
 
    std::vector<int> GetIntVector(const std::string &name);
    std::vector<float> GetFloatVector(const std::string &name);
    std::vector<std::string> GetStringVector(const std::string &name);
    
    bool GetToStack(const std::string &variableName);
   
    template<typename T>
    T Lua_Get(const std::string &variableName)
    {
        return 0;
    }
    
    template<typename T>
    T Lua_GetDefault()
    {
        return 0;
    }
    
    private:
    lua_State* L;
    std::string _filename;
    int _level; 
};

template<>
inline std::string LuaScript::Lua_GetDefault<std::string>()
{
    return "null";
}

template<>
inline bool LuaScript::Lua_Get<bool>(const std::string &variableName)
{
    return (bool)lua_toboolean(L, -1);
}

template<>
inline float LuaScript::Lua_Get<float>(const std::string &variableName)
{
    if(!lua_isnumber(L, -1))
    {
        PrintError(variableName, "Not a number");
    }
    return (float)lua_tonumber(L, -1);
}

template<>
inline std::string LuaScript::Lua_Get<std::string>(const std::string &variableName)
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
