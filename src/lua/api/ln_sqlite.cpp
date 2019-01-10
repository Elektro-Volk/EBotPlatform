/*
ln_sqlite.cpp
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
#include "ln_sqlite.h"
#include "sqlite3.h"
#ifdef __linux__
#include <mysql/mysql.h>
#else
#include "mysql.h"
#endif

#include "lua/ELua.hpp"
#include <mutex>

struct sqlite_object {
	std::mutex m_lock;
	sqlite3 *sqlite;
};

void ln_sqlite::init_api(lua_State* L)
{
	lua_register(L, "sqlite", ln_sqlite::connect);
  	// mysql_connection
	luaL_newmetatable(L, "sqlite_db");
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");

	lua_pushstring(L, "__call");
	lua_pushcfunction(L, ln_sqlite::execute);
	lua_settable(L, -3);

  	lua_pop(L, 1);
}

int ln_sqlite::connect(lua_State* L)
{
	const char* filename = luaL_checkstring(L, 1);
	sqlite3 *sqlite;

	// Init sqlite
	if (sqlite3_open(filename, &sqlite)) luaL_error(L, sqlite3_errmsg(sqlite));

	// Create structure
	sqlite_object* object = new sqlite_object();
	object->sqlite = sqlite;

	// Push lua
	lua_pushlightuserdata(L, object);
  	luaL_getmetatable(L, "sqlite_db");
  	lua_setmetatable(L, -2);

  	return 1;
}

int ln_sqlite::execute(lua_State* L)
{
	sqlite_object *object = (sqlite_object*)luaL_checkudata(L, 1, "sqlite_db");
	std::lock_guard<std::mutex> locker(object->m_lock);
	const char* query = luaL_checkstring(L, 2);

	// Prepare query
	sqlite3 *sqlite = object->sqlite;
	int nStrings = lua_gettop(L) - 1;
	lua_getglobal(L, "string");
	lua_getfield(L,-1, "format");
	lua_pushstring(L, query);

	for (int i = 1; i < nStrings; i++) {
		const char *from = luaL_checkstring(L, i + 2);
    	char to[256];
    	unsigned long len = mysql_escape_string(to, from, strlen(from));
		to[len] = '\0';
		lua_pushstring(L, to);
	}
	e_lua->safeCall(L, nStrings, 1);
	query = luaL_checkstring(L, -1);
	lua_settop(L, 0);

  	// Do SQL query
	sqlite3_stmt *stmt;
	int rc = sqlite3_prepare_v2(sqlite, query, -1, &stmt, NULL);
	if (rc != SQLITE_OK) { object->m_lock.unlock(); luaL_error(L, "%s [%s]", sqlite3_errmsg(sqlite), query); }
	printf(query);
	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		//const unsigned char *name = sqlite3_column_text(stmt, 1);
		// ...
		//printf(name);
		printf(id+"");
	}
	if (rc != SQLITE_DONE) { object->m_lock.unlock(); luaL_error(L, "%s [%s]", sqlite3_errmsg(sqlite), query); }
	sqlite3_finalize(stmt);

  	/*if (mysql_query(mysql, query)) { object->m_lock.unlock(); luaL_error(L, "%s [%s]", mysql_error(mysql), query); };
	MYSQL_RES *res = mysql_store_result(mysql);
	if (!res) return 0; // null response

  	// Get values
  	MYSQL_FIELD *fields = mysql_fetch_fields(res);
  	lua_newtable(L);
  	for(int n = 1; MYSQL_ROW row = mysql_fetch_row(res); n++) {
    	lua_pushinteger(L, n);
    	lua_newtable(L);
		unsigned long *lengths;
		lengths = mysql_fetch_lengths(res);
		for (int i = 0; i < mysql_num_fields(res); i++) {
      		lua_pushstring(L, fields[i].name);
			switch(fields[i].type) {
            	case MYSQL_TYPE_TINY:
                case MYSQL_TYPE_SHORT:
                case MYSQL_TYPE_LONG:
                case MYSQL_TYPE_INT24:
                case MYSQL_TYPE_FLOAT:
                case MYSQL_TYPE_DOUBLE:
					lua_pushinteger(L, std::stoi(row[i])); break;
      			default: lua_pushlstring(L, row[i], lengths[i]); break;
			}
      		lua_settable(L, -3);
    	}
    	lua_settable(L, -3);
   	}
    mysql_free_result(res);*/
    return 1;
}
