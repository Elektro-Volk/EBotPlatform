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
