//
//  ELongPoll.cpp
//  EBotPlatform
//
//  Created by Elektro-Volk on 16/07/2018.
//
//
#include "ELongPoll.hpp"
#include "core/EConsole.hpp"

ELongPoll *e_longpoll;

ELongPoll::ELongPoll()
{

}

void ELongPoll::start()
{
    this->getServer();
}

void ELongPoll::getServer()
{
    e_console->log("LP", "Получение LongPoll сервера...");
	/*con::log("Получение LongPoll сервера...");

  string method = "groups.getLongPollServer";
	Document document = vk::jSend(method, {{ "group_id", vk::groupid->value }});
	Value &data = document["response"];

	server = data["server"].GetString();
	params["key"] = data["key"].GetString();
	params["ts"] = to_string(data["ts"].GetInt());*/
    e_console->log("LP", "LongPoll сервер получен.");
}

void ELongPoll::frame()
{
    e_console->log("LP", "Кадр движка EBP");
	/*while (true) {
		while(!luawork::isWorking){}
		Document data;
		data.Parse(net::POST(server, params).c_str());
    // Check data
		if(!data.IsObject()) continue;
		if(data.HasMember("failed")) { processError(data); continue; }
    // Get value
		params["ts"] = data["ts"].GetString();
    // Process updates
		Value &updates = data["updates"];
		for (int i = 0; i < updates.Size(); i++) processMessage(updates[i]);
	}*/
}

/*void ELongPoll::processError(rapidjson::Document &err)
{
  con::log("Ошибка LongPoll: " + to_string(err["failed"].GetInt()));
  if (err["failed"].GetInt() != 1) getServer();
  else params["ts"] = to_string(err["ts"].GetInt());
}

void ELongPoll::processMessage(rapidjson::Value &upd)
{
  //if(upd["type"] != "message_new") return; // This is not a message
  //if(longpoll::lp_debug->getBool()) con::log("Сообщение LongPoll: " + to_string(upd["object"]["id"].GetInt()));
  //luawork::push(upd["object"]);
}*/

ELongPoll::~ELongPoll() {}
