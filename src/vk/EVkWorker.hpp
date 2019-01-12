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
#include <map>
#include "rapidjson/document.h"
#include "core/ECvarSystem.hpp"
#include "EVkLinster.hpp"

class EVkWorker {
private:
public:
	cvar vk_longpoll = new Cvar("vk_longpoll", "Use longpoll or callback", "1");
	cvar vk_debugevents = new Cvar("vk_debugevents", "Debug new group events", "0");
	cvar vk_cbtoken = new Cvar("vk_cbtoken", "CallBack confirmation token", "0");
	cvar vk_cbaddress = new Cvar("vk_cbaddress", "CallBack server address", "http://localhost:80");

	EVkLinster* linster;

	EVkWorker();
	void initStart();
	void start();
	void frame();
	void stop();
    ~EVkWorker();
};

extern EVkWorker *e_vkworker;
