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
#include "ELuaModules.hpp"
#include "core/EConsole.hpp"
#include "core/EFilesystem.hpp"
#include "api/lu_other.h"

ELuaModules::ELuaModules()
{

}

void ELuaModules::loadModules(lua_State *L)
{
    e_console->log("Lua", "Загрузка модулей...");
    for (auto it = modules.begin(); it != modules.end(); ++it)
    {
    	lua_pushfstring(L, "scripts/modules/%s", it->name.c_str());
    	if (lu_other::connect(L)) {
    		it->isLoaded = !lua_isstring(L, -1);
    		if (!it->isLoaded) e_console->error("Lua::" + it->name, lua_tostring(L, -1));
            if (!lua_istable(L, -1)) {
                e_console->error("Lua::" + it->name, "Модуль вернул не таблицу.");
                continue;
            }
    		lua_setglobal(L, it->name.c_str());
    	}
    	lua_settop(L, 0);
    }
}

void ELuaModules::clearModules()
{
    modules.clear();
}

void ELuaModules::startModules(lua_State *L)
{
    for (auto it = modules.begin(); it != modules.end(); ++it)
	{
		lua_getglobal(L, it->name.c_str());
        lua_getfield(L, -1, "CheckInstall");
        if(!lua_isnil(L, -1) && lua_pcall(L, 0, LUA_MULTRET, 0))
            e_console->error("Lua::" + it->name, lua_tostring(L, -1));

        lua_getglobal(L, it->name.c_str());
        lua_getfield(L, -1, "Start");
        if(!lua_isnil(L, -1) && lua_pcall(L, 0, LUA_MULTRET, 0))
            e_console->error("Lua::" + it->name, lua_tostring(L, -1));
		lua_settop(L, 0);
    }
}

void ELuaModules::load()
{
    std::vector<string> loaddata = e_fs->dirList("scripts/modules");
	for (auto e : loaddata) {
		string name = e;
		name.erase( name.end() - 4, name.end());
		modules.push_back({ name, false });
    }
}

ELuaModules::~ELuaModules()
{

}
