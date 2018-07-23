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
#include "ECommandline.hpp"
#include "EConsole.hpp"

ECommandline *e_commandline;

ECommandline::ECommandline(int argc, char *argv[])
{
    string param = "";
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] == '-') { // Param
            param = string(argv[i]).substr(1);
            continue;
        }

        if (param != "") {
            params.insert ({ param, string(argv[i]) });
            param = "";
        }
    }
}

string ECommandline::getValue(string param, string def)
{
    if (params.find(param) == params.end()) return def;
    return params[param];
}

ECommandline::~ECommandline()
{

}
