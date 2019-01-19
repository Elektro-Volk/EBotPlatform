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
#include "core/EConsole.hpp"
#include "ELuaError.hpp"
#include "ELuaJson.hpp"

EThreadPoolWorker::EThreadPoolWorker(int tid)
:enabled(true), busy(false), thread(&EThreadPoolWorker::loop, this)
{
    id[0] = tid;
	L = lua_newthread(e_lua->state->getState());
    lua_setfield(e_lua->state->getState(), LUA_REGISTRYINDEX, id);
}

void EThreadPoolWorker::loop()
{
    while (enabled) {
        std::unique_lock<std::mutex> locker(mutex);
    	cv.wait(locker, [&](){ return busy || !enabled; });

    	if (!busy) continue;
		job(L);
        busy = false;
    }
}

bool EThreadPoolWorker::isBusy()
{
    return busy;
}

void EThreadPoolWorker::add(std::function<void(lua_State*)> job)
{
    std::unique_lock<std::mutex> locker(mutex);
    this->busy = true;
	this->job = job;
	cv.notify_one();
}

EThreadPoolWorker::~EThreadPoolWorker()
{
    enabled = false;
    while(busy){}
    cv.notify_one();
    thread.join();
}
