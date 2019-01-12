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


void ECallback::handle(web::http::http_request message)
{
	e_console->log("CB", "запрос");
	message.reply(status_codes::OK, "LOL");
}

ECallback::ECallback()
{
	e_console->log("CB", "Создание CallBack сервера...");
	auto address = utility::conversions::to_string_t(e_vkworker->vk_cbaddress->getString());
	m_listener = web::http::experimental::listener::http_listener(address);
	m_listener.support(methods::GET, std::bind(&ECallback::handle, this, std::placeholders::_1));

	try
	{
		m_listener
			.open()
			.wait();
	}
	catch (std::exception const& e)
	{
		e_console->error("CB", e.what());
	}

	e_console->log("CB", "CallBack сервер успешно создан по адресу: " + conversions::to_utf8string(m_listener.uri().to_string()));
}

void ECallback::frame()
{
	if (!isWork) {
		std::this_thread::yield(); // CPU 100% hack :)
		return;
	}

}

ECallback::~ECallback() 
{
	m_listener.close().wait();
}
