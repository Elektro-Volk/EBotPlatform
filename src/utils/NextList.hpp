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
