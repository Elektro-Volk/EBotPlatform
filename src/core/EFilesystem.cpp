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
#include "EFilesystem.hpp"
#include <fstream>
#include <streambuf>
#include <sys/stat.h>
#include "dirent.h"

EFilesystem *e_fs;

EFilesystem::EFilesystem()
{
    // TODO: get root from concmdparser
}

void EFilesystem::existsAssert(string path)
{
    if (!exists(path)) throw std::runtime_error("файл `" + path + "` не найден.");
}

bool EFilesystem::exists(string path)
{
    std::ifstream infile(bot_root + "/" + path);
    return infile.good();
}

string EFilesystem::readAll(string path)
{
    std::ifstream file(bot_root + "/" + path);
    return string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

std::vector<string> EFilesystem::readLines(string path)
{
    std::vector<string> result;

    std::ifstream file(bot_root + "/" + path);
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

std::vector<string> EFilesystem::dirList(string _dir)
{
    std::vector<string> data;
#ifdef __linux__
    DIR *dir = opendir((_dir[0] == '/' ? _dir : bot_root + '/' + _dir).c_str());
    if(dir)
    {
        struct dirent *ent;
        while((ent = readdir(dir)) != NULL)
        {
            string f = ent->d_name;
            if(f != "." && f != "..")
            data.push_back(f);
        }
    }
#else
    string search_path = (_dir[0] == '/' ? _dir : bot_root + '/' + _dir) + "/*.*";
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
    if(hFind != INVALID_HANDLE_VALUE) {
        do {
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                data.push_back(fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd));
        ::FindClose(hFind);
    }
#endif
    return data;
}

EFilesystem::~EFilesystem ()
{
}
