//
//  CvarSystem.hpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#pragma once
#include <string>
#include <map>

class Cvar {
private:
    std::string name, desc, value;
public:
    Cvar(std::string name, std::string desc, std::string def);
    void setValue(std::string new_value);
    std::string getString();
    int getInt();
    float getFloat();
    bool getBool();
    ~Cvar();
};

typedef Cvar* cvar;

extern std::map<std::string, cvar> e_cvars;
