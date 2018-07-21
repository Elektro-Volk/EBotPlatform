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

EThreadPoolWorker::EThreadPoolWorker()
:enabled(true), busy(false), thread(&EThreadPoolWorker::loop, this)
{
    e_net->handles.insert({ thread.get_id(), curl_easy_init() });

    id[0] = e_lua->pool->nWorkers++;
	//L = lua_newthread(luawork::state);
    //lua_setfield(luawork::state, LUA_REGISTRYINDEX, id);
    e_console->log("Поток", "new " + std::to_string(id[0]));
}

void EThreadPoolWorker::loop()
{
    while (enabled) {
        std::unique_lock<std::mutex> locker(mutex);
    	cv.wait(locker, [&](){ return busy || !enabled; });

    	if (!busy) continue;
        /*lua_unlock(L);
        luawork::safeCall(L, 1);
        lua_lock(L);*/
        e_console->log("Поток", "do " + std::to_string(id[0]));
        busy = false;
    }
}

bool EThreadPoolWorker::isBusy()
{
    return busy;
}

void EThreadPoolWorker::add(rapidjson::Value &msg)
{
    std::unique_lock<std::mutex> locker(mutex);
    busy = true;

    /*lua_unlock(L);
    lua_settop(L, 0);
    lua_getglobal(L, "NewMessage");
    lua_json::pushValue(L, msg);
    lua_lock(L);*/
    e_console->log("Поток", "+ " + std::to_string(id[0]));
    cv.notify_one();
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
