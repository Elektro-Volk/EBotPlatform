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
	lua_register(L, "uptime", lu_other::uptime);
	lua_register(L, "relua", lu_other::relua);
	lua_register(L, "getId", lu_other::getId);
	lua_register(L, "connect", lu_other::connect);
	lua_register(L, "resp", lu_other::resp);

	luaL_loadfile(L, "core.lua");
	lua_pcall(L, 0, LUA_MULTRET, 0);
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
