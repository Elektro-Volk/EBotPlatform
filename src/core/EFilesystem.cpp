//
//  EFilesystem.cpp
//  EGGIN
//
//  Created by Elektro-Volk on 29/06/2018.
//
//

#include "EFilesystem.hpp"
#include <fstream>
#include <streambuf>

std::string EFilesystem::readAll(std::string path)
{
    std::ifstream file(path);
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

std::vector<std::string> EFilesystem::readLines(std::string path)
{
    std::vector<std::string> result;

    std::ifstream file(path);
    for(std::string line; getline(file, line);) result.push_back(line);

    return result;
}

void EFilesystem::writeAll(std::string path, std::string data)
{
    
}

void EFilesystem::writeLine(std::string path, std::string data)
{

}
