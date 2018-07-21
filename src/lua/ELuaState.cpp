/*
    Copyright Elektro-Volk 2018
    EMail: elektro-volk@yandex.ru
    VK: https://vk.com/ebotp

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
