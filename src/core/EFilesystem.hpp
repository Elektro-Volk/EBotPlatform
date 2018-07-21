#pragma once
#include "common.hpp"
#include <vector>

class EFilesystem {
public:
    string bot_root = "bot";

    EFilesystem();
    string readAll(string path);
    std::vector<string> readLines(string path);
    void writeAll(string path, string data);
    void writeLine(string path, string data);
    ~EFilesystem();
};

extern EFilesystem *e_fs;
