/*
ln_cmd.cpp
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
#include "ln_cmd.h"
#include "common.hpp"
#include "lua/ELuaJson.hpp"
#include "core/ECmd.hpp"
#include <vector>;

void ln_cmd::init_api(lua_State *L)
{
  lua_createtable(L, 0, 1);

  luaapi_tablefunc(L, ln_cmd::exec, "exec");
  luaapi_tablefunc(L, ln_cmd::exists, "exists");
  luaapi_tablefunc(L, ln_cmd::exe, "exe");
  luaapi_tablefunc(L, ln_cmd::parse, "parse");
  luaapi_tablefunc(L, ln_cmd::data, "data");

  lua_setglobal(L, "cmd");
}

// void exec (path)
int ln_cmd::exec(lua_State * L)
{
    try {
    	e_cmd->exec(luaL_checkstring(L, 1));
    	return 0;
    }
    catch (const std::runtime_error& error) {
        luaL_error(L, error.what());
    }
}

// bool exists (cmd_name)
int ln_cmd::exists(lua_State * L)
{
	lua_pushboolean(L, e_cmd->exists(luaL_checkstring(L, 1)));
	return 1;
}

// string exe (cmd_name)
int ln_cmd::exe(lua_State * L)
{
	e_cmd->exe(luaL_checkstring(L, 1));
	return 0;
}

// table parse (line)
int ln_cmd::parse(lua_State * L)
{
	auto parsed = e_cmd->parse(luaL_checkstring(L, 1));

	lua_newtable(L);
	for (int i = 0; i < parsed.size(); i++) {
		lua_pushnumber(L, i+1); // Key
		lua_pushstring(L, parsed[i].c_str()); // Value
		lua_settable(L, -3);
	}
	return 1;
}

// string data (table)
int ln_cmd::data(lua_State * L)
{
  luaL_checktype(L, 1, LUA_TTABLE);
  int offset = luaL_checkinteger(L, 2);

	std::vector<string> args;
	lua_pushnil(L);
	while (lua_next(L, 1))
	{
		lua_pushvalue(L, -1);
		args.push_back(luaL_checkstring(L, -1));
		lua_pop(L, 2);
	}
	lua_pushstring(L, e_cmd->data(args, offset).c_str());

	return 1;
}
