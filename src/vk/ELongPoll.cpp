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
#include "ELongPoll.hpp"
#include "core/EConsole.hpp"
#include "core/ENet.hpp"
#include "vk/EVkApi.hpp"
#include "lua/ELua.hpp"
#include <thread>

using namespace rapidjson;

ELongPoll *e_longpoll;

ELongPoll::ELongPoll()
{

}

void ELongPoll::start()
{
    this->getServer();
    isWork = true;
}

void ELongPoll::stop()
{
    isWork = false;
}

void ELongPoll::getServer()
{
    e_console->log("LP", "Получение LongPoll сервера...");

	Document document = e_vkapi->jSend("groups.getLongPollServer", {{ "group_id", e_vkapi->vk_groupid->getString() }});
    if(document.HasMember("error")) throw std::runtime_error(document["error"]["error_msg"].GetString());

    Value &data = document["response"];
	server = data["server"].GetString();
	params["act"] = "a_check";
	params["key"] = data["key"].GetString();
	params["ts"] = std::to_string(data["ts"].GetInt());

    e_console->log("LP", "LongPoll сервер получен.");
}

void ELongPoll::frame()
{
    if (!isWork) {
        std::this_thread::yield(); // CPU 100% hack :)
        return;
    }

    Document data;
	data.Parse(e_net->sendPost(server, params).c_str());
    // Check data
	if(!data.IsObject()) return;
	if(data.HasMember("failed")) { processError(data); return; }
    // Get value
	params["ts"] = data["ts"].GetString();
    // Process updates
	Value &updates = data["updates"];
	for (int i = 0; i < updates.Size(); i++) processMessage(updates[i]);
}

void ELongPoll::processError(rapidjson::Document &err)
{
  e_console->log("LP", "Ошибка: " + std::to_string(err["failed"].GetInt()));
  if (err["failed"].GetInt() != 1) getServer();
  else params["ts"] = std::to_string(err["ts"].GetInt());
}

void ELongPoll::processMessage(rapidjson::Value &upd)
{
  if(upd["type"] != "message_new") return; // This is not a message
  e_console->log("LP", "Сообщение: " + std::to_string(upd["object"]["id"].GetInt()));

  e_lua->add(upd["object"]);
}

ELongPoll::~ELongPoll() {}
