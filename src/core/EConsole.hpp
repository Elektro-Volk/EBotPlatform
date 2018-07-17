//
//  Console.hpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#pragma once
#include "common.hpp"
#include <sstream>

class EConsole {
private:
    bool isEcho = true;
    std::stringstream echo_buffer;
public:
    EConsole();
    void setEcho(bool value);
	string getBuffer();
    void log(std::string type, std::string text);
    ~EConsole();
protected:

};

extern EConsole* e_console;
