#pragma once
#include "luaheaders.hpp"

class ELuaState {
private:
    lua_State *state;
public:
    ELuaState();
    ~ELuaState();
protected:

};
