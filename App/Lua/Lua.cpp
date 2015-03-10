
// Includes.
#include "App/Lua/Lua.h"

// Lua.
extern "C"
{
#include "lauxlib.h"
#include "lualib.h"
}

luabridge::lua_State *Lua::state()
{
    static Lua lua;
    return lua.lua_state_;
}

Lua::Lua() : lua_state_(luabridge::luaL_newstate())
{
    luaL_openlibs(lua_state_);
}

Lua::~Lua()
{
    lua_close(lua_state_);
}
