#include "lua/luaheaders.hpp"

#define luaapi_tablefunc(L, func, name) lua_pushcfunction(L, func); lua_setfield (L, -2, name);
