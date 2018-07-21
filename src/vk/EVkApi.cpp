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
#include "EVkApi.hpp"
#include "core/ENet.hpp"

EVkApi *e_vkapi;

EVkApi::EVkApi()
{

}

string EVkApi::send(string method, std::map<string, string> params)
{
    if(params.find("access_token") == params.end()) params["access_token"] = vk_token->getString();
    params["v"] = vk_version->getString();
    return e_net->sendPost("https://api.vk.com/method/" + method, params);
}

rapidjson::Document EVkApi::jSend(string method, std::map<string, string> params)
{
    rapidjson::Document data;
    data.Parse(this->send(method, params).c_str());
    /*if (data.HasMember("error") && data["error"]["error_code"].GetInt() == 6) { // time
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        return this->jSend(method, params);
    }*/
    return data;
}

EVkApi::~EVkApi()
{

}
