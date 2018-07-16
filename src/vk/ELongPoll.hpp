//
//  ELongPoll.hpp
//  EBotPlatform
//
//  Created by Elektro-Volk on 16/07/2018.
//
//

#pragma once

class ELongPoll {
private:
    void getServer();
public:
    ELongPoll();
    void start();
    void frame();
    ~ELongPoll();
};

extern ELongPoll *e_longpoll;
