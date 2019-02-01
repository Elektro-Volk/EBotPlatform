/*
ln_timers.h
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
#pragma once
#include "luaapi.h"
#include "common.hpp"
#include <map>
#include <mutex>

namespace ln_timers {
	struct timer {
		string code; // Function code
		int next;
		int period;
		int count;
	};

	extern std::map<int, timer> timers;
	extern std::mutex mutex;

	void init_api(lua_State *L);
	int create(lua_State *L);
	int get_function(lua_State *L);
	int destroy(lua_State *L);

	// In engine
	void loop();
	void clear();
}
