//
//  ECmd.hpp
//  EGGIN
//
//  Created by Elektro-Volk on 02/07/2018.
//
//

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
