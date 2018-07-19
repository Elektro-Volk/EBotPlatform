//
//  ELongPoll.hpp
//  EBotPlatform
//
//  Created by Elektro-Volk on 16/07/2018.
//
//

#pragma once
#include "common.hpp"
#include "rapidjson/document.h"
#include <map>

class ELongPoll {
private:
    bool isWork = false;
    std::map<string, string> params;
    string server;

    void getServer();
    void processError(rapidjson::Document &err);
    void processMessage(rapidjson::Value &upd);
public:
    ELongPoll();
    void start();
    void stop();
    void frame();
    ~ELongPoll();
};

extern ELongPoll *e_longpoll;
