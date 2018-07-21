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
#include "EBotPlatform.hpp"
#include "EConsole.hpp"
#include "ECmd.hpp"
#include "ENet.hpp"
#include "EFilesystem.hpp"
#include "vk/EVkApi.hpp"
#include "vk/ELongPoll.hpp"
#include "lua/ELua.hpp"


bool EBotPlatform::isWork = true;

int main()
{
    EBotPlatform::initEngine();
    while (EBotPlatform::isWork) { EBotPlatform::frame(); }
    return 0;
}

int EBotPlatform::initEngine()
{
    try {
        // Init Core
        e_fs = new EFilesystem();
        e_console = new EConsole();
        e_cmd = new ECmd();
        e_net = new ENet();
        e_vkapi = new EVkApi();
        e_longpoll = new ELongPoll();
        e_lua = new ELua();

        e_console->log("CORE", "EBotPlatform V1.0.0.");
        e_console->log("CORE", "Электро-Волк 2016-2018.");

        e_console->setEcho(false);
        e_cmd->exec("config.cfg");
        e_console->setEcho(true);

        e_longpoll->start();
        e_lua->start();
    }
    catch (const std::runtime_error& error) {
        e_console->error("CRASH", error.what());
        EBotPlatform::shutdown();
    }
    return 0;
}

void EBotPlatform::frame()
{
    e_longpoll->frame();
}

void EBotPlatform::shutdown()
{
    isWork = false;
}
