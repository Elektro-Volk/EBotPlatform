//
//  NextList.cpp
//  EBotPlatform
//
//  Created by Elektro-Volk on 16/07/2018.
//
//

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
