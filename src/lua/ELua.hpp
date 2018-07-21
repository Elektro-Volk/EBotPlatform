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
#pragma once
#include "core/ECvarSystem.hpp"
#include "ELuaState.hpp"
#include "EThreadPool.hpp"

class ELua {
private:
public:
    cvar lua_file = new Cvar("lua_file", "Lua main file", "main.lua");
    cvar pool_count = new Cvar("pool_count", "Lua threads count", "1");

    ELuaState *state;
    EThreadPool *pool;

    ELua();
    void start();
    void stop();
    void reload();
    void add(rapidjson::Value &msg);
    ~ELua();
protected:

};

extern ELua *e_lua;
