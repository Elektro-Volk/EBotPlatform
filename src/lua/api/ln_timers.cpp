/*
ln_timers.cpp
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
#include "ln_timers.h"
#include <thread>
#include "common.hpp"
#include "core/EConsole.hpp"
#include <condition_variable>
#include "lua/ELua.hpp"

std::map<int, ln_timers::timer> ln_timers::timers = std::map<int, ln_timers::timer>();
std::mutex ln_timers::mutex;

void ln_timers::init_api(lua_State *L)
{
  lua_createtable(L, 0, 1);

  luaapi_tablefunc(L, ln_timers::create, "ncreate");
  luaapi_tablefunc(L, ln_timers::get_function, "get_function");
  luaapi_tablefunc(L, ln_timers::destroy, "destroy");

  string str = "return function(p,c,f,...)local d={...}; return timers.ncreate(p,c,function()f(table.unpack(d))end)end";
  luaL_loadbuffer(L, str.c_str(), str.size(), "timers.create");
  lua_call(L, 0, 1);
  lua_setfield(L, -2, "create");

  lua_setglobal(L, "timers");

//e_console->log("TIMERS", "Создан новый таймер #"+std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
  //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
 // e_console->log("TIMERS", "Создан новый таймер #"+std::to_string(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
}

// int timers.create(period, count, func)
int ln_timers::create(lua_State *L)
{
	int period = lua_tointeger(L, 1);    // Period
	int count = lua_tointeger(L, 2);     // Count
	luaL_checktype(L, 3, LUA_TFUNCTION); // Function

	if (count == 0) count = -100; // Forever

	// Get id
	int id = 1;
	while (timers.find(id) != timers.end()) id++;

	lua_pushstring(L, ("timer_" + std::to_string(id)).c_str());
	lua_insert(L, 3);
	lua_settable(L, LUA_REGISTRYINDEX);

	int this_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

	std::unique_lock<std::mutex> locker(mutex);
	timers.insert(std::pair<int, timer>(id, { "timer_"+std::to_string(id), this_time + period, period, count }));
	locker.unlock();
	if (timers.size() == 1) std::thread(loop).detach();

    //e_console->log("TIMERS", "Создан новый таймер #"+std::to_string(id));
    //e_console->log("TIMERS", "Кол-во таймеров: "+std::to_string(timers.size()));

	lua_pushinteger(L, id);
	return 1;
}

// function timers.get_function(id)
int ln_timers::get_function(lua_State *L)
{
	int id = lua_tointeger(L, 1);
	auto ent = timers.find(id);
	if (ent == timers.end()) luaL_error(L, "timer %i not found", id);
	lua_pushstring(L, ("timer_" + std::to_string(ent->first)).c_str());
	lua_gettable(L, LUA_REGISTRYINDEX);
	return 1;
}

// timers.destroy(id)
int ln_timers::destroy(lua_State *L)
{
	int id = lua_tointeger(L, 1);
	if (timers.find(id) == timers.end()) luaL_error(L, "timer %i not found", id);
	timers.erase(id);
	return 0;
}

void ln_timers::loop()
{
	while(true) {
		int min_time = -100;
		std::unique_lock<std::mutex> locker(mutex);
        int this_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		for (auto &ent : timers) {
            //e_console->log("TIMERS", std::to_string(this_time)+"#"+std::to_string(ent.second.next));
			if (this_time >= ent.second.next) {
				// Trigger timer
				e_lua->pool->add([ent](lua_State* L) {
					lua_unlock(L);
					lua_pushstring(L, ("timer_" + std::to_string(ent.first)).c_str());
					lua_gettable(L, LUA_REGISTRYINDEX);
					e_lua->safeCall(L, 0);
					lua_settop(L, 0);
					lua_lock(L);
				});

				ent.second.next = this_time + ent.second.period;
				if (ent.second.count != -100)
					if (ent.second.count <= 1) {
						timers.erase(ent.first);
						min_time = 0;
						break;
					}
					else
						ent.second.count--;
			}
			else if (ent.second.next - this_time < min_time || min_time == -100)
				min_time = ent.second.next - this_time;
		}
		locker.unlock();

		if (timers.size() == 0) return;
		if(min_time!=0) std::this_thread::sleep_for(std::chrono::milliseconds(min_time));
	}
}
