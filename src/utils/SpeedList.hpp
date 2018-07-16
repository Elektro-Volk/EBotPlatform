#pragma once
#include <mutex>

template<class Type>
class SpeedList {
private:
	int m_size = 0;
	Type* m_data = nullptr;
	std::mutex m_lock;
public:
	SpeedList<Type>();
	void push(Type element);
	void pop(Type element);
	void flush();
	int getSize();
	Type& operator [] (int i);
	~SpeedList();
};
