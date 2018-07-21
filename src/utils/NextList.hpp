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
#include <mutex>

template<class Key, class Value>
class NextList {
private:
    struct _L {
		struct _L* next = nullptr;
		Key key;
		Value value;
	};

    int m_size = 0;
	_L* m_data = nullptr;
	std::mutex m_lock;
public:
    NextList<Key, Value>();
    void push(Key key, Value value);
	void pop(Key key);
	void flush();
	int getSize();
	Value& operator [] (Key key);
    ~NextList();
protected:
};
