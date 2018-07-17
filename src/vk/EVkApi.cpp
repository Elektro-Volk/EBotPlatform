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
