#include "EFilesystem.hpp"
#include <fstream>
#include <streambuf>

EFilesystem *e_fs;

EFilesystem::EFilesystem()
{
    // TODO: get root from concmdparser
}

string EFilesystem::readAll(string path)
{
    std::ifstream file(path);
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

std::vector<string> EFilesystem::readLines(string path)
{
    std::vector<string> result;

    std::ifstream file(path);
    for(string line; getline(file, line);) result.push_back(line);

    return result;
}

void EFilesystem::writeAll(string path, string data)
{
    // TODO
}

void EFilesystem::writeLine(string path, string data)
{
    // TODO
}

EFilesystem::~EFilesystem ()
{
}
