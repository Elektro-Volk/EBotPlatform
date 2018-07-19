//
//  Console.cpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#include "EConsole.hpp"
#include <iostream>

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

/* Log message to console */
// type - message type | text - message
void EConsole::log(std::string type, std::string text)
{
    (isEcho ? std::cout : echo_buffer)
        << "\x1b[34m[\x1b[34;1m" << currentDateTime() << "\x1b[0;34m]"
        << " [\x1b[34;1m" << type << "\x1b[0;34m] "
        << "\x1b[0m" << text
        << std::endl;
}

void EConsole::error(std::string type, std::string text)
{
    (isEcho ? std::cerr : echo_buffer)
        << "\x1b[34m[\x1b[34;1m" << currentDateTime() << "\x1b[0;34m]"
        << " [\x1b[31;5m" << type << "\x1b[0;34m] "
        << "\x1b[0m" << text
        << std::endl;
}

/* Shutdown console and log */
EConsole::~EConsole()
{

}
