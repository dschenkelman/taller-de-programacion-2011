#pragma once
#include <exception>

//inline class to easily follow template inclusion model
template<class T>
class List
{
private:
	size_t count;
	size_t currentSize;
	T* items;
	enum {initialItems = 10, sizeDifferential = 10};
	void resize(size_t differential)
	{
		size_t initialSize = this->currentSize;
		//keep reference to old memory to copy and delete
		T* aux = this->items;

		//increase current size
		currentSize = currentSize + differential;
		this->items = new T[currentSize];
		
		//copy elements to new container
		size_t endSize = currentSize > initialSize ?  initialSize : currentSize;

		for (size_t i = 0; i < endSize; i++)
		{
			this->items[i] = aux[i];
		}

		//delete previous container
		delete aux;
	}
	void increaseSize()
	{
		this->resize(this->sizeDifferential);
	}
	void decreaseSize()
	{
		this->resize(-this->sizeDifferential);
	}
public:
	List(void) : count(0), currentSize(initialItems)
	{
		this->items = new T[initialItems];
	}
	
	~List(void)
	{
		delete items;
	}

	void add(const T& item)
	{
		if (this->count == this->currentSize)
		{
			this->increaseSize();	
		}
		this->items[this->count] = item;
		this->count++;
	}
	
	T removeLast()
	{
		if (this->count == 0)
		{
			throw std::exception();
		}
		(this->count)--;
		
		if (this->count < (this->currentSize - this->sizeDifferential))
		{
			this->decreaseSize();	
		}
		
		return this->items[this->count];
	}
	
	T at(size_t position)
	{
		if (position < 0 || position >= this->count)
		{
			throw std::exception();
		}
		return this->items[position];
	}
	
	size_t length()
	{
		return this->count;
	}

	size_t capacity()
	{
		return this->currentSize;
	}
};