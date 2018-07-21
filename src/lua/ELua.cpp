#include "ELua.hpp"
#include "core/EConsole.hpp"
#include "ELuaError.hpp"

ELua *e_lua;

ELua::ELua()
{

}

void ELua::start()
{
    try {
        state = new ELuaState();
        pool = new EThreadPool();
    }
    catch (ELuaError& err) {
        e_console->error("Lua", "При загрузке Lua скриптов возникла ошибка.");
        e_console->error("Lua", "Исправьте все ошибки и перезагрузите скрипты командой `relua`.");
        e_console->error("Lua", err.what());

        if (state) delete state;
        if (pool) delete pool;
    }
}

void ELua::reload()
{

}

void ELua::add(rapidjson::Value &msg)
{
    if (state == nullptr) throw std::runtime_error("Lua is not working.");
    pool->add(msg);
}

ELua::~ELua()
{

}
