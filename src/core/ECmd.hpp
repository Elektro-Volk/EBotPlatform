//
//  ECmd.hpp
//  EGGIN
//
//  Created by Elektro-Volk on 02/07/2018.
//
//

#pragma once
#include <vector>
#include <map>
#include <string>

typedef std::vector<std::string> ECmdArgs;
typedef std::string (*ECmdFunction)(ECmdArgs args);

struct ECmdCommand
{ std::string name; ECmdFunction function; std::string desc; };

class ECmd {
private:
    std::map<std::string, ECmdCommand> commands;
public:
    ECmd();
	void add(std::string cmd_name, ECmdFunction function, std::string cmd_desc);
	void exe(std::string text);
	ECmdArgs parse(std::string line);
	bool exists(const std::string cmd_name);
	void exec(const std::string cpath);
    ~ECmd();
};

extern ECmd* e_cmd;
