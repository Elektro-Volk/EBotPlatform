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
#include "NextList.hpp"

template<class Key, class Value>
NextList<Key, Value>::NextList() { }

template<class Key, class Value>
void NextList<Key, Value>::push(Key key, Value value)
{
    std::lock_guard<std::mutex> locker(m_lock);
    m_data = new _L({ m_data, key, value });
    m_size++;
}

template<class Key, class Value>
void NextList<Key, Value>::pop(Key key)
{
    std::lock_guard<std::mutex> locker(m_lock);
    _L *last = m_data;
    for (_L *el = m_data; el != nullptr; el = el->next) {
        if (key != el->key) { last = el; continue; }

        last->next = el->next;
        m_size--;
        delete el;
        break;
    }
}

template<class Key, class Value>
void NextList<Key, Value>::flush() {
    std::lock_guard<std::mutex> locker(m_lock);
    _L *next = m_data;
    while (next != nullptr) {
        _L *el = next;
        next = next->next;
        delete el;
    }
	m_size = 0;
}

template<class Key, class Value>
Value& NextList<Key, Value>::operator [] (Key key)
{
    std::lock_guard<std::mutex> locker(m_lock);
    for (_L *el = m_data; el != nullptr; el = el->next)
        if (key == el->key) return el->value;
    throw 0;
}

template<class Key, class Value>
int NextList<Key, Value>::getSize() {
	return m_size;
}

template<class Key, class Value>
NextList<Key, Value>::~NextList()
{
    flush();
}
