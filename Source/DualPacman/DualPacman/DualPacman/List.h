#pragma once
#include <exception>
#include <iostream>

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
		delete []aux;
	}


	void increaseSize()
	{
		this->resize(this->sizeDifferential);
	}

	void decreaseSize()
	{
		this->resize(-this->sizeDifferential);
	}

	bool shouldDecreaseSize() const
	{
		return this->count < (this->currentSize - this->sizeDifferential);
	}

	bool isWithinBounds(size_t index) const
	{
		return !(index < 0 || index >= this->count);
	}

	void populateItemsFromList(const List& l)
	{
		this->items = new T[l.capacity()];

		for (size_t i = 0; i < l.length(); i++)
		{
			this->items[i] = l.at(i);
		}
	}

public:
	List() : count(0), currentSize(initialItems)
	{
		this->items = new T[initialItems];
	}

	List(const List& l) : count(l.length()), currentSize(l.capacity())
	{
		this->populateItemsFromList(l);
	}

	~List(void)
	{
		delete []items;
	}

	List& operator=(const List& l)
	{
		if (this == &l) 
		{
			return *this;
		}
		// reset list
		delete []items;
		
		// initialize
		currentSize = l.capacity();
		count = l.length();
		populateItemsFromList(l);

		return *this;
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

	T removeAt(size_t position)
	{
		if (!this->isWithinBounds(position))
		{
			throw std::exception();
		}

		T item = this->items[position];
		
		for (size_t i = position + 1; i < this->count; i++)
		{
			this->items[i - 1] = this->items[i];
		}

		this->count--;

		if (this->shouldDecreaseSize())
		{
			this->decreaseSize();
		}

		return item;
	}


	T removeLast()
	{
		return this->removeAt(this->count - 1);
	}

	T& at(size_t position) const
	{
		if (!this->isWithinBounds(position))
		{
			throw std::exception();
		}
		return this->items[position];
	}

	size_t length() const
	{
		return this->count;
	}

	size_t capacity() const
	{
		return this->currentSize;
	}

	T& operator[](size_t index) const
	{
		return this->at(index);
	}

	void clear(void)
	{
		while (this->count != 0)
		{
			this->removeLast();
		}
	}

	T getValueAt(size_t position) const
	{
		if (!this->isWithinBounds(position))
		{
			throw std::exception();
		}
		return this->items[position];
	}

	bool contains(T value) const
	{
		for (size_t i = 0; i < this->count; i++)
		{
			if (this->items[i] == value)
			{
				return true;
			}
		}

		return false;
	}
};