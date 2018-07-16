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
