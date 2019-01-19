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
#include "common.hpp"
#include <thread>
#include <mutex>
#include "rapidjson/document.h"
#include "luaheaders.hpp"

class EThreadPoolWorker {
private:
    char id[1];
    bool busy;
    bool enabled;

    std::condition_variable cv;
    std::mutex mutex;
    std::thread thread;

    lua_State* L;

    void loop();
public:
	std::function<void(lua_State*)> job;

    EThreadPoolWorker(int id);
    bool isBusy();
    void add(std::function<void(lua_State*)> job);
    ~EThreadPoolWorker();
protected:

};
