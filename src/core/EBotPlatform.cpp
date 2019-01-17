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
#include "ECommandline.hpp"
#include "EConsole.hpp"
#include "ECmd.hpp"
#include "ENet.hpp"
#include "EFilesystem.hpp"
#include "vk/EVkApi.hpp"
#include "vk/EVkWorker.hpp"
#include "lua/ELua.hpp"


bool EBotPlatform::isWork = true;
const string EBotPlatform::version = "19.1a";
const int EBotPlatform::start_time = time(0);

int main(int argc, char *argv[])
{
#ifndef __linux__
	//std::locale::global(std::locale(""));
//	std::locale::global(std::locale("ru_RU.UTF-8"));
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
#endif
    EBotPlatform::startEngine(argc, argv);
    return 0;
}

int EBotPlatform::startEngine(int argc, char *argv[])
{
    try {
        // Init Core
        e_commandline = new ECommandline(argc, argv);
        e_console = new EConsole();
        e_fs = new EFilesystem();
        e_cmd = new ECmd();
        e_net = new ENet();
        e_vkapi = new EVkApi();
        e_vkworker = new EVkWorker();
        e_lua = new ELua();

		e_console->log("", " \x1b[31;5m-------------------====\x1b[0m+\x1b[31;5m====-------------------\x1b[0m");
		e_console->log("", "                     {_| |_}     EBotPlatform V" + version);
        e_console->log("", "                   /| _|_|_ |\\   Электро-Волк 2016-2019.");
        e_console->log("", "                  ( |/_____\\| )                 ");
        e_console->log("", "               |--`/_/  |  \\_\\'--|              ");
        e_console->log("", "           ____   //( ) |    \\\\   ____          ");
        e_console->log("", "          | ++ |==|\\___/ \\___/|==| ++ |         ");
        e_console->log("", "           \\__/   |  ___ ___  |   \\__/          ");
        e_console->log("", "                 __\\/oo X []\\/__                ");
        e_console->log("", "                || [\\__/_\\__/] ||               ");
        e_console->log("", "               ~~~~           ~~~~              ");

        e_console->setEcho(false);
        e_cmd->exec("config.cfg");
        e_console->setEcho(true);

        e_lua->start();
		e_vkworker->start();
    }
    catch (const std::runtime_error& error) {
        e_console->setEcho(true);
        e_console->error("CRASH", error.what());
        EBotPlatform::shutdown();
    }
    return 0;
}

void EBotPlatform::shutdown()
{
    isWork = false;
}
