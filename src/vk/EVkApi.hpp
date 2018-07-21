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

class EVkApi {
private:
public:
    cvar vk_token = new Cvar("vk_token", "VK group token", "-");
    cvar vk_groupid = new Cvar("vk_groupid", "VK bot group id", "-");
    cvar vk_version = new Cvar("vk_version", "VK Api version", "5.80");

    EVkApi();
    string send(string method, std::map<string, string> params = {});
    rapidjson::Document jSend(string method, std::map<string, string> params = {});
    ~EVkApi();
};

extern EVkApi *e_vkapi;
