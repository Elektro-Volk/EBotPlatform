//
//  EGGIN.cpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#include "EBotPlatform.hpp"
#include "EConsole.hpp"
#include "ECmd.hpp"
#include "ENet.hpp"
#include "vk/ELongPoll.hpp"


bool EGGIN::isWork = true;

int main()
{
    EGGIN::initEngine();
    while (EGGIN::isWork) { EGGIN::frame(); }
    return 0;
}

int EGGIN::initEngine()
{
    // Init Core
    e_console = new EConsole();
    e_cmd = new ECmd();
    e_net = new ENet();

    e_console->log("CORE", "Инициализация EBotPlatform V1.0.0...");
    e_console->log("CORE", "Электро-Волк 2016-2018.");

    e_longpoll = new ELongPoll();

    e_longpoll->start();

    return 0;
}

void EGGIN::frame()
{
    e_longpoll->frame();
}

void EGGIN::shutdown()
{
    isWork = false;
}
