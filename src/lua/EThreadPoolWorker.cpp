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
#include "EThreadPoolWorker.hpp"
#include "ELua.hpp"
#include "core/ENet.hpp"
#include "core/EConsole.hpp"
#include "ELuaError.hpp"
#include "ELuaJson.hpp"

EThreadPoolWorker::EThreadPoolWorker()
:enabled(true), busy(false), thread(&EThreadPoolWorker::loop, this)
{
    e_net->handles.insert({ thread.get_id(), curl_easy_init() });

    id[0] = e_lua->pool->nWorkers++;
	L = lua_newthread(e_lua->state->getState());
    lua_setfield(e_lua->state->getState(), LUA_REGISTRYINDEX, id);
}

void EThreadPoolWorker::loop()
{
    while (enabled) {
        std::unique_lock<std::mutex> locker(mutex);
    	cv.wait(locker, [&](){ return busy || !enabled; });

    	if (!busy) continue;
        lua_unlock(L);
        e_lua->safeCall(L, 1);
        lua_lock(L);
        busy = false;
    }
}

bool EThreadPoolWorker::isBusy()
{
    return busy;
}

void EThreadPoolWorker::add(string type, rapidjson::Value &msg)
{
    std::unique_lock<std::mutex> locker(mutex);
    busy = true;

    try {
        lua_unlock(L);
        lua_settop(L, 0);

        lua_getglobal(L, "vk_events");
        if (lua_isnil(L, -1)) throw ELuaError("Global table `vk_events` not found");
        lua_getfield(L, -1, type.c_str());
        if (lua_isnil(L, -1)) throw ELuaError("Function `vk_events['" + type + "']` not found");

        ELuaJson::C2L::pushValue(L, msg);

        lua_lock(L);
        cv.notify_one();
    }
    catch (ELuaError& err) {
        e_console->error("Lua", err.what());
        lua_lock(L);
        busy = false;
    }
}

EThreadPoolWorker::~EThreadPoolWorker()
{
    enabled = false;
    while(busy){}
    curl_easy_cleanup(e_net->handles[thread.get_id()]);
    e_net->handles.erase(thread.get_id());
    cv.notify_one();
    thread.join();
}
