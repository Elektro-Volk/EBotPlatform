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
#include "ELuaJson.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"

using namespace rapidjson;

void ELuaJson::C2L::pushObject(lua_State *L, const rapidjson::Value &j)
{
    lua_newtable(L);
    for (Value::ConstMemberIterator it = j.MemberBegin(); it != j.MemberEnd(); ++it) {
        lua_pushstring(L, it->name.GetString());
        if(pushValue(L, it->value)) lua_settable(L, -3); else lua_pop(L, 1);
    }
}

void ELuaJson::C2L::pushArray(lua_State *L, const rapidjson::Value &array)
{
    lua_newtable(L);
    for (int i = 0; i < array.Size(); i++) {
        lua_pushinteger(L, i + 1);
        if(pushValue(L, array[i])) lua_settable(L, -3); else lua_pop(L, 1);
    }
}

bool ELuaJson::C2L::pushValue(lua_State *L, const rapidjson::Value &value)
{
    switch (value.GetType()) {
        case 1: { lua_pushboolean(L, false); break; }
        case 2: { lua_pushboolean(L, true ); break; }
        case 3: { pushObject(L, value); break; }
        case 4: { pushArray(L, value); break; }
        case 5: { lua_pushstring(L, value.GetString()); break; }
        case 6: {
            if(value.IsDouble()) lua_pushnumber(L, value.GetDouble());
            else lua_pushinteger(L, value.GetInt());
            break;
        }
        default: { return false; break; }
    }
    return true;
}
