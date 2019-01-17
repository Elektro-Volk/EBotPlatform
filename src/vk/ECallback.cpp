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
#include "ECallback.hpp"
#include "core/EConsole.hpp"
#include "core/ENet.hpp"
#include "vk/EVkApi.hpp"
#include "lua/ELua.hpp"
#include "EVkWorker.hpp"
#include <thread>

#include "cpprest/containerstream.h"
#include "cpprest/filestream.h"
#include "cpprest/http_client.h"
#include "cpprest/http_listener.h"
#include "cpprest/json.h"
#include "cpprest/producerconsumerstream.h"

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace rapidjson;

void ECallback::handle(web::http::http_request message)
{
	Document data;
	data.Parse(message.extract_utf8string(true).get().c_str());
	if(!data.IsObject()) return;

	if(e_vkworker->vk_cbsecret->getString() != "" && e_vkworker->vk_cbsecret->getString() != data["secret"].GetString()) {
		message.reply(status_codes::OK, "incorrect secret");
		return;
	}

	while(!e_vkworker->isWork) { std::this_thread::yield(); }

	if(std::string(data["type"].GetString()) == std::string("confirmation")) {
		message.reply(status_codes::OK, e_vkworker->vk_cbtoken->getString());
		e_console->log("CB", "CallBack сервер успешно подтверждён.");
	}
	else {
		if(e_vkworker->vk_debugevents->getBool())
			e_console->log("LP", "Cобытие: " + string(data["type"].GetString()));
		e_lua->add(data["type"].GetString(), data["object"]);
		message.reply(status_codes::OK, "ok");
	}
}

ECallback::ECallback()
{
	e_console->log("CB", "Запуск CallBack сервера...");
	auto address = utility::conversions::to_string_t(e_vkworker->vk_cbaddress->getString());
	m_listener = web::http::experimental::listener::http_listener(address);
	m_listener.support(methods::POST, std::bind(&ECallback::handle, this, std::placeholders::_1));

	try
	{
		m_listener.open().wait();
	}
	catch (std::exception const& e)
	{
		e_console->error("CB", e.what());
	}

	e_console->log("CB", "CallBack успешно запущен.");
	while(true) std::this_thread::sleep_for(std::chrono::seconds(30)); // Magick value
}

ECallback::~ECallback()
{
	m_listener.close().wait();
}
