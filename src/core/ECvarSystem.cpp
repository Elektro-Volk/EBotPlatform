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
