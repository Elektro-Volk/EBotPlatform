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
#include "EConsole.hpp"
#include <iostream>
#include <ctime>
#ifdef _WIN32
	int __write_w32(FILE* fp, const char* buf);
	#include "windows.h"
#endif

EConsole* e_console;

// Util TODO
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%X", localtime(&now));

    return buf;
}

/* Initialize console and log file */
EConsole::EConsole()
{

}

void EConsole::setEcho(bool value)
{
	if (value) echo_buffer.clear();
	isEcho = value;
}

string EConsole::getBuffer()
{
	return echo_buffer.str();
}

#ifdef __linux__
#define __write_w32(a, b) a<<b
#endif

/* Log message to console */
// type - message type | text - message
void EConsole::log(std::string type, std::string text)
{
	std::string str = "\x1b[34m[\x1b[34;1m" + currentDateTime() + "\x1b[0;34m]" + " [\x1b[34;1m" + type + "\x1b[0;34m] " + "\x1b[0m" + text + "\n";
	if (isEcho)
		__write_w32(stdout, str.c_str());
	else
		echo_buffer << str;
}

void EConsole::error(std::string type, std::string text)
{
	std::string str = "\x1b[34m[\x1b[34;1m" + currentDateTime() + "\x1b[0;34m]" + " [\x1b[31;5m" + type + "\x1b[0;34m] " + "\x1b[0m" + text + "\n";
	if (isEcho)
		__write_w32(stdout, str.c_str());
	else
		echo_buffer << str;
}

void EConsole::print(std::string text)
{
}

/* Shutdown console and log */
EConsole::~EConsole()
{

}
