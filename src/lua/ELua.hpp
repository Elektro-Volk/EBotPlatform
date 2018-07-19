#pragma once
#include "core/ECvarSystem.hpp"
#include "ELuaState.hpp"
#include "EThreadPool.hpp"

class ELua {
private:
public:
    cvar lua_file = new Cvar("lua_file", "Lua main file", "main.lua");
    cvar pool_count = new Cvar("pool_count", "Lua threads count", "1");

    ELuaState *state;
    EThreadPool *pool;

    ELua();
    void start();
    void stop();
    void reload();
    void add(rapidjson::Value &msg);
    ~ELua();
protected:

};

extern ELua *e_lua;
