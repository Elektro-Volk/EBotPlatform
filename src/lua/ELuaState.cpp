#include "ELuaState.hpp"
#include "ELua.hpp"
#include "ELuaError.hpp"
#include "core/EFilesystem.hpp"

ELuaState::ELuaState()
{
    //luaModules::load();
    state = luaL_newstate();
    luaL_openlibs(state);
    //init_lua_api(state);

    //luaModules::loadModules(state);
    string lua_path = e_fs->bot_root + "/scripts/" + e_lua->lua_file->getString();
    if(luaL_loadfile(state, lua_path.c_str()) || lua_pcall(state, 0, LUA_MULTRET, 0))
        throw ELuaError(state);

    //luaModules::startModules(state);
}

ELuaState::~ELuaState()
{

}
