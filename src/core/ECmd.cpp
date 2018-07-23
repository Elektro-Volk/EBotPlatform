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

/* REWORK THIS!!! */

#include "ECmd.hpp"
#include "EConsole.hpp"
#include "EBotPlatform.hpp"
#include "ECvarSystem.hpp"
#include "EFilesystem.hpp"
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <thread>

ECmd* e_cmd;

void cmd_help(std::vector<string> args)
{
	e_console->log("CMD", "Список команд EBotPlatform V" + EBotPlatform::version);
	for (auto cmd : e_cmd->commands) {
		e_console->log("CMD", cmd.first + " - " + cmd.second.desc);
	}
}

ECmd::ECmd()
{
	std::thread(&ECmd::readLoop, this).detach();
	add ("help", cmd_help, "вывод всех команд EBP");
}

bool ECmd::exists(const std::string cmd_name)
{
	return commands.find(cmd_name) != commands.end();
}

void ECmd::add(std::string cmd_name, ECmdFunction function, std::string cmd_desc)
{
	//if (exists(cmd_name)) return con::error(cmd_name +" already defined");
	//if (cvars::exists(cmd_name)) return con::error(cmd_name+" already defined as a cvar");
	commands[cmd_name] = { cmd_name, function, cmd_desc };
}

void ECmd::exe(const std::string text)
{
	if (text == "") return;
	ECmdArgs cmd_args = parse(text);
	std::string cmd_name = cmd_args[0];

    // Command
    if (commands.find(cmd_name) != commands.end()) {
        commands[cmd_name].function(cmd_args);
    }
    else if(e_cvars.find(cmd_name) != e_cvars.end()) {
        if (cmd_args.size() == 2) e_cvars[cmd_name]->setValue(cmd_args[1]);
        e_console->log("CMD", cmd_name + " = " + e_cvars[cmd_name]->getString());
    }
    else e_console->error("CMD", "Команда `" + cmd_name + "` не найдена");
}

ECmdArgs ECmd::parse(std::string text)
{
	bool nospace = 0;
	int index = 0;
	ECmdArgs cmd_args;

	if (text.empty()) return ECmdArgs();
	if (text.find(' ') == std::string::npos) {
		cmd_args.push_back(text);
		return cmd_args;
	}

	cmd_args.push_back("");
	for (int i = 0;i < strlen(text.c_str());i++) {
		char ch = text.c_str()[i];
		if (ch == ' ' && !nospace) {
			index++;
			cmd_args.push_back("");
		}
		else if (ch == '"')
			nospace = !nospace;
		else
			cmd_args[index] += ch;
	}
	return cmd_args;
}



void ECmd::exec(string cpath)
{
	e_fs->existsAssert(cpath);
	std::vector<string> lines = e_fs->readLines(cpath);
	for (string line : lines)
	{
		if (line == "" || line.front() == '#') continue;
		exe(line);
	}
}

string ECmd::data(std::vector<string> cmd_args, int sub)
{
	if (cmd_args.size() < sub) return "";
	string ret = "";
	for (int i = sub-1; i < cmd_args.size(); i++)
	{
		ret += " " + cmd_args[i];
	}
	return ret.substr(1);
}

void ECmd::readLoop()
{
	for (string line; true; std::getline(std::cin, line)) exe(line);
}

ECmd::~ECmd()
{
}
