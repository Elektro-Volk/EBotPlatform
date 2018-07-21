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
#include "common.hpp"
#include <vector>
#include <map>

typedef std::vector<string> ECmdArgs;
typedef string (*ECmdFunction)(ECmdArgs args);

struct ECmdCommand
{ string name; ECmdFunction function; string desc; };

class ECmd {
private:
    std::map<string, ECmdCommand> commands;
public:
    ECmd();
	void add(string cmd_name, ECmdFunction function, string cmd_desc);
	void exe(string text);
	ECmdArgs parse(string line);
	bool exists(const string cmd_name);
	void exec(const string cpath);
    ~ECmd();
};

extern ECmd* e_cmd;
