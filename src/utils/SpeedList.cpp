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
#include "SpeedList.hpp"

template<class Type>
SpeedList<Type>::SpeedList() { }

template<class Type>
void SpeedList<Type>::push(Type element)
{
    std::lock_guard<std::mutex> locker(m_lock);
    int s = sizeof(Type);
    m_data = (Type*)(m_size == 0 ? malloc(s) : realloc(m_data, (m_size + 1) * s));
    m_data[m_size] = element;
    m_size++;
}

template<class Type>
void SpeedList<Type>::pop(Type element)
{
    std::lock_guard<std::mutex> locker(m_lock);
    Type *new_array = (Type*)malloc((m_size - 1) * sizeof(Type));
    int new_i = 0;
    for (int i = 0; i < m_size; i++) {
        if (m_data[i] == element) continue;
        new_array[new_i] = m_data[i];
        new_i++;
    }
    free(m_data);
    m_data = new_array;
    m_size--;
}

template<class Type>
void SpeedList<Type>::flush() {
	free(m_data);
	m_data = nullptr;
	m_size = 0;
}

template<class Type>
Type& SpeedList<Type>::operator [] (int i)
{
	return m_data[i];
}

template<class Type>
int SpeedList<Type>::getSize() {
	return m_size;
}

template<class Type>
SpeedList<Type>::~SpeedList()
{
    flush();
}
