//
//  CvarSystem.cpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#include "ECvarSystem.hpp"

std::map<std::string, cvar> e_cvars;

Cvar::Cvar(std::string name, std::string desc, std::string def)
{
    this->name = name; this->desc = desc; this->value = def;
    e_cvars.insert(std::pair<std::string, cvar>(name, this));
}

void Cvar::setValue(std::string new_value)
{
    value = new_value;
}

std::string Cvar::getString()
{
    return value;
}

int Cvar::getInt()
{
    return std::stoi(value);
}

float Cvar::getFloat()
{
    return std::stof(value);
}

bool Cvar::getBool()
{
    return value == "1";
}

Cvar::~Cvar()
{
    e_cvars.erase(name);
}
