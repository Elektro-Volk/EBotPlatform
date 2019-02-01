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
#include "ELua.hpp"
#include "core/ECmd.hpp"
#include "core/EConsole.hpp"
#include "vk/EVkWorker.hpp"
#include "ELuaError.hpp"
#include "ELuaJson.hpp"
#include "rapidjson/writer.h"

#include "api/ln_timers.h" // Clear

ELua *e_lua;

void cmd_relua(std::vector<string> args)
{
	e_lua->reload();
}

ELua::ELua()
{
    e_cmd->add("relua", cmd_relua, "перезагрузить Lua скрипты");
}

void ELua::start()
{
    try {
        state = new ELuaState();
        pool = new EThreadPool();

		e_vkworker->enable();
        e_console->log("Lua", "Скрипты были успешно запущены.");
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
	e_console->log("Lua", "Перезагрузка скриптов и модулей...");

	e_vkworker->disable();
	ln_timers::clear();
	if (pool) delete pool;
	if (state) delete state;

	start();
}

void ELua::add(string type, rapidjson::Value &msg)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	msg.Accept(writer);
	string s = buffer.GetString();

    pool->add([type, s](lua_State* L) {
		try {
			lua_unlock(L);
			lua_getglobal(L, "vk_events");
			if (lua_isnil(L, -1)) throw ELuaError("Global table `vk_events` not found");
			lua_getfield(L, -1, type.c_str());
			if (lua_isnil(L, -1)) throw ELuaError("Function `vk_events['" + type + "']` not found");
			lua_pushstring(L, s.c_str());
			ELuaJson::decode(L);
			e_lua->safeCall(L, 1);
			lua_settop(L, 0);
			lua_lock(L);
		}
		catch (ELuaError& err) {
			e_console->error("Lua", err.what());
			lua_lock(L);
		}
	});
}

void ELua::call(lua_State* L, int argnum, int retnum)
{
    if(lua_pcall(L, argnum, retnum, 0)) throw ELuaError(L);
}


bool ELua::safeCall(lua_State* L, int argnum, int retnum)
{
  try {
      call(L, argnum, retnum);
      return true;
  }
  catch (ELuaError& err) {
      e_console->error("Lua", err.what());
      return false;
  }
}

ELua::~ELua()
{

}
