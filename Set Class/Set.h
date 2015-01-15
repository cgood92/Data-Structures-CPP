﻿/***********************************************************************
* Program:
*    Lesson 01, Sets
*    Brother Sloan, CS 235
* Author:
*	Clint Goodman and Parker Hubbard
* Summary:
************************************************************************/

#ifndef SET_H
#define SET_H
#include <cassert>

//#include <vector>
#include <iostream>
#include <string>
using namespace std;

//early declaration of the "SetIterator" class for the "Vector" class
template <class T>
class SetIterator;
/**********************************************************************
* Set
* //creating the class for sets
***********************************************************************/
template <class T>
class Set
{
private:
	T * data;          // dynamically allocated array of T
	//I switched "size" for "numItems"
	int current_size;          //the current Set size, or number of items
	//currently within the vector
	int capacity_size;      // how many items can I put on the Set before full?
	void resize(int newCapacity) throw (bad_alloc);

public:
	/////////constructors///////////////////
	// default constructor : empty and kinda useless
	Set() : data(NULL), current_size(0), capacity_size(0) {}
	// copy constructor : copy it
	Set(const Set<T> & rhs) : data(NULL), current_size(0), capacity_size(0)
	{
		if (rhs.size())   { *this = rhs; }
	}
	// non-default constructor : pre-allocate
	Set(int capacity) : data(NULL), current_size(0), capacity_size(0)
	{
		if (capacity > 0) { resize(capacity); }
	}
	// destructor : free everything that was previously used
	~Set()
	{
		if (NULL != data)//(capacity)
		{  //assert(capacity);
			delete[] data;
		}
	}
	//operator=
	Set<T> & operator = (const Set<T> & rhs) throw (bad_alloc);

	//operator[]
	Set<T> & operator [] (const Set<T> & rhs) throw (bool);

	//operator()//return-by-value
	T operator () (int index) throw (bool)
	{
		return (*this)[index];
	}

	//Return the Setsize
	int size()        const{ return current_size; }

	//Test whether the set is empty
	bool empty()      const { return current_size == 0; }

	//returns the capacity_size size
	int capacity()    const{ return capacity_size; }

	// remove all the items from the container
	void clear()      { current_size = 0; }

	// return an iterator to the beginning of the list
	SetIterator <T> begin()   { return SetIterator<T>(data); }

	// return an iterator to the end of the list
	SetIterator <T> end()     { return SetIterator<T>(data + current_size); }

	//not int, but return the type of variable being used (char, int, float..)
	SetIterator<T> find(T element);

	void insert(const T & item);
	void erase(const SetIterator <T> & tIterator);

	Set<T> operator || (const Set<T> & rhs);
	Set<T> operator && (const Set<T> & rhs);
};


/**********************************************************************
***********************************************************************/
template <class T>
void Set<T> ::insert(const T & item)
{
	//If this is first insert, allocate some space, insert it, and quit
	if (current_size == 0)
	{
		resize(1);
		data[0] = item;
		current_size++;
		return;
	}

	SetIterator<T> iter_find = find(item);

	/* If iterator returned is the same as the end, but the item is not the last,
	this means that the item was not found, so we can insert it */
	if (*iter_find == data[current_size - 1] && data[current_size - 1] != item)
	{
		//If full, increase capacity
		if (current_size == capacity_size)
		{
			resize(capacity_size * 2);
		}
		//"i" is pulled out to this scope so we can use it a few lines down
		int i;
		for (i = this->current_size; data[i] > item; i--)
		{
			data[i] = data[i + 1];
		}
		data[i] = item;
		this->current_size++;
	}
}


/**********************************************************************
***********************************************************************/
template <class T>
SetIterator<T> Set<T> ::find(T element)
{
	int iBegin = 0;
	int iEnd = current_size - 1;
	while ((iBegin == iEnd) || (iBegin < iEnd))
	{
		int iMiddle = (iBegin + iEnd) / 2;
		if (element == data[iMiddle])
		{
			return SetIterator<T>(data, iMiddle - 1);
		}
		if (element < data[iMiddle])
		{
			iEnd = iMiddle - 1;
		}
		else
		{
			iBegin = iMiddle + 1;
		}
	}
	return SetIterator<T>(data, current_size - 1);

}



/**********************************************************************
***********************************************************************/
template <class T>
void Set<T> ::erase(const SetIterator<T> & tIterator)
{

}

/**********************************************************************
***********************************************************************/
template <class T>
Set<T> Set<T> ::operator && (const Set<T> & rhs)
{
	//TODO
	return rhs;
}

/**********************************************************************

***********************************************************************/
template <class T>
Set<T> Set<T> ::operator || (const Set<T> & rhs)
{
	//TODO
	return rhs;
}

/**********************************************************************
* Set-resize
* //creating the steps for resizing the Set
***********************************************************************/
template <class T>
void Set<T> ::resize(int newCapacity) throw (bad_alloc)
{
	//allocate new array
	T * pNew;
	pNew = new T[newCapacity];
	//copy data from old array
	for (int i = 0; i < current_size; i++)
	{
		pNew[i] = data[i];
	}
	//delete old and assign the new
	delete[] data;
	data = pNew;
	capacity_size = newCapacity;
}

/**********************************************************************
* Set-operator equals
* //creating the steps for equaling the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator = (const Set<T> & rhs) throw (bad_alloc)
{
	current_size = 0; //remove all previously in the data
	//make sure we are big enough for the data
	if (rhs.current_size > capacity_size)
	{
		resize(rhs.current_size);
	}
	assert(capacity_size >= rhs.current_size);

	//copy the data from the other size
	current_size = rhs.current_size;
	for (int i = 0; i < rhs.current_size; i++)
	{
		data[i] = rhs.data[i];
	}
	//return itself
	return *this;
}
/**********************************************************************
* Set-operator brackets
* //creating the steps for partitioning the Set
***********************************************************************/
template <class T>
Set<T> & Set<T> :: operator [] (const Set<T> & rhs) throw (bool)
{
	if ((rhs < 0) || (rhs > current_size))
	{
		throw true;
	}
	return data[rhs]; //return-by-reference
}
/**********************************************************************
* SetIterator
* //creating the class of the SetIterator
***********************************************************************/
template <class T>
class SetIterator
{
private:
	T * p;
public:
	// default constructor - set value to "0"?
	SetIterator() : p(0x00000000)  {}
	// initialize to direct the private variable "t" to some item
	SetIterator(T * p) : p(p)      {}
	SetIterator(T * pInput, int index)
	{
		this->p = pInput;
		for (int i = 0; i < index; i++)
			p++;
	}
	//copy constructor
	SetIterator(const SetIterator & rhs)
	{
		*this = rhs;
	}
	// assignment operator

	SetIterator & operator = (const SetIterator & rhs)
	{
		this->p = rhs.p;
		return *this;
	}
	// not equals operator
	bool operator != (const SetIterator & rhs) const
	{
		return rhs.p != this->p;
	}
	// equals operator
	bool operator == (const SetIterator & rhs) const
	{
		return rhs.p == this->p;
	}
	// dereference operator
	T & operator * ()
	{
		return *p;
	}
	// prefix decrement
	SetIterator <T> & operator -- ()
	{
		p--;
		return *this;
	}
	// postfix decrement
	SetIterator <T> & operator--(int prefix)
	{
		SetIterator tmp(*this);
		p--;
		return tmp;
	}
	// prefix increment
	SetIterator <T> & operator ++ ()
	{
		p++;
		return *this;
	}
	// postfix increment
	SetIterator <T> & operator++(int postfix)
	{
		SetIterator tmp(*this);
		p++;
		return tmp;
	}
};
#endif