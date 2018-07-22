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

class EFilesystem {
public:
    string bot_root = "bot";

    EFilesystem();
    void existsAssert(string path);
    bool exists(string path);
    string readAll(string path);
    std::vector<string> readLines(string path);
    void writeAll(string path, string data);
    void writeLine(string path, string data);
    std::vector<string> dirList(string _dir);
    ~EFilesystem();
};

extern EFilesystem *e_fs;
