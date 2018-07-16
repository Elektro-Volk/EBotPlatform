//
//  Console.hpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#pragma once
#include <string>

class EConsole {
private:
public:
    EConsole();
    void log(std::string type, std::string text);
    ~EConsole();
protected:

};

extern EConsole* e_console;
