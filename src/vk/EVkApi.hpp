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
