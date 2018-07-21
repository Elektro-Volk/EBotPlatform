#pragma once
#include "common.hpp"
#include "lua.h"

class ELuaError {
private:
    string error_msg;
public:
    ELuaError (lua_State *L) { error_msg = lua_tostring(L, -1); }
    ELuaError (string str) { error_msg = str; }
    string what () { return error_msg; }
    ~ELuaError() {}
};
