#pragma once
#include "List.h"

template<class T>
class Stack
{
private:
	List<T>* items;
public:
	Stack(void)
	{
		this->items = new List<T>();
	}
	~Stack(void)
	{
		delete this->items;
	}

	T peek()
	{
		return this->items->at(this->items->length() - 1);
	}

	T pop()
	{	
		return this->items->removeLast();		
	}
	
	void push(const T& item)
	{
		this->items->add(item);
	}

	size_t count()
	{
		return this->items->length();
	}
};
