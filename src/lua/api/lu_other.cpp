/*
lu_other.cpp
Copyright (C) 2018 Elektro-Volk
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#include "lu_other.h"
#include "common.hpp"
#include "lua/ELuaJson.hpp"
#include "lua/ELua.hpp"
#include "core/EBotPlatform.hpp"
#include "core/EFilesystem.hpp"
#include "core/EConsole.hpp"
#include "vk/EVkApi.hpp"
#include "utils/strutils.hpp"
#include <map>
#include <thread>
#include "lua/api/ln_vkapi.h"

void lu_other::init_api(lua_State *L)
{
  lua_register(L, "trand", lu_other::randtable);
  lua_register(L, "uptime", lu_other::uptime);
  lua_register(L, "relua", lu_other::relua);
  lua_register(L, "getId", lu_other::getId);
  lua_register(L, "addline", lu_other::addline);
  lua_register(L, "connect", lu_other::connect);
  lua_register(L, "resp", lu_other::resp);

  luaL_loadstring(L, "function toint (str) return str and tonumber(str) and math.floor(tonumber(str)) end");
  lua_pcall(L, 0, 0, 0);
  luaL_loadstring(L, "function ischat (msg) return msg.peer_id > 2000000000 end");
  lua_pcall(L, 0, 0, 0);
  luaL_loadstring(L, "function getcid (msg) return msg.peer_id - 2000000000 end");
  lua_pcall(L, 0, 0, 0);
}

int lu_other::randtable(lua_State *L)
{
  lua_settop(L, 1);
  luaL_checktype(L, 1, LUA_TTABLE);
  lua_len(L,1);
  int len = lua_tointeger(L,-1) - 1;
  lua_pushinteger(L,1+rand()%len);
  lua_rawget(L,1);
  return 1;
}

// int uptime()
int lu_other::uptime(lua_State *L)
{
  lua_pushinteger(L, time(0)-EBotPlatform::start_time);
  return 1;
}

int lu_other::relua(lua_State *L)
{
  e_lua->reload();
  return 0;
}

// int uptime()
int lu_other::getId(lua_State *L)
{
  std::string url = luaL_checkstring(L, 1);
	if (url.find("/") != std::string::npos) {
		auto tokens = strutils::split(url, '/');
		url = tokens[tokens.size() - 1];
	}

	rapidjson::Value &result = e_vkapi->jSend("utils.resolveScreenName", {{"screen_name", url}})["response"];
  if(!result.IsObject()) return 0;
	if (result.HasMember("object_id")) lua_pushinteger(L, result["object_id"].GetInt()); else lua_pushnil(L);
	return 1;
}

// int uptime()
int lu_other::addline(lua_State *L)
{
  const char* line = luaL_checkstring(L, 2);
	lua_getfield(L, 1, "message"); // Get message
	if (lua_isnil(L, -1))
	{
		lua_pushstring(L, line);
	}
	else {
		lua_pushfstring(L, "%s\n%s", luaL_checkstring(L, -1), line);
	}
	lua_setfield(L, 1, "message");
	return 0;
}

// int uptime()
int lu_other::connect(lua_State *L)
{
  const char *path = lua_tostring(L, 1);
	lua_getglobal(L, "require");
	lua_pushfstring(L, "%s/%s", e_fs->bot_root.c_str(), path);
  if(lua_pcall(L, 1, -1, 0))
    luaL_error(L, lua_tostring(L, -1));
	return 1;
}

// int uptime()
int lu_other::resp(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TTABLE);
	if (lua_isstring(L, 2)) {
		lua_newtable(L);
		lua_insert(L, 2);
		lua_setfield(L, -2, "message");
	}
	lua_getfield(L, 1, "peer_id");
	lua_setfield(L, 2, "peer_id");

	lua_pushstring(L, "messages.send");
    lua_remove(L, 1);
	lua_insert(L, 1);// STR TAB
	return ln_vkapi::vk_jSend(L);
}
