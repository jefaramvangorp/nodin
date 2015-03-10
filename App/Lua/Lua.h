#ifndef APP_LUA_LUA_H_
#define APP_LUA_LUA_H_

// LuaBridge.
#include <LuaBridge.h>

// Lua.
extern "C" {
#include "lua.h"
}

class Lua
{
public:

    static luabridge::lua_State* state();

private:

    Lua();
    ~Lua();

    luabridge::lua_State* lua_state_;
};
#endif // APP_LUA_LUA_H_
