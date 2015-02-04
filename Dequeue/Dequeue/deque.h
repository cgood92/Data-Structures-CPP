/***********************************************************************
 * Program:
 *    Lesson 3, Dequeue
 *    Brother Sloan, CS 235
 * Author:
 *      Clint Goodman and Parker Hubbard
 * Summary:
 ************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <iostream>
#include <string>
using namespace std;

/**********************************************************************
 * Stack
 * //creating the class for Stacks
 ***********************************************************************/
template <class T>
class Deque
{
  private:
     T * data;      //dynamically allocated array of T
     int frontSpot; //the "X" value of where the bottom/front item is found
     int backSpot;  //the "X" value of where the top/back item is found
     int current_size;  //the current Set size, or number of items
     int capacity_size; //how many items can I put on the Set before full?
     void resize(int newCapacity) throw (bad_alloc);
  public:
     ////////////CLASS CONSTRUCTORS///////////////////
     // default constructor :
     Deque() : data(NULL), current_size(0), capacity_size(0),
        frontSpot(-1), backSpot(-1){}
     // copy constructor : copy details of another indicated
     Deque(const Deque<T> & rhs) : current_size(0), data(NULL)
     {
        resize(rhs.capacity_size);
        current_size = rhs.current_size;
        capacity_size = rhs.capacity_size;
        frontSpot = rhs.frontSpot;
        backSpot = rhs.backSpot;
        for (int i = 0; i <= rhs.backSpot; i++)
           data[i] = rhs.data[i];
     }
     // non-default constructor : pre-allocate
     Deque(int capacity) : data(NULL), current_size(0),
         capacity_size(0), frontSpot(-1), backSpot(-1)
     {
        if (capacity > 0) { resize(capacity); }
     }
     // destructor : free everything that was previously used
     ~Deque()
     {
        if (NULL != data)//(capacity)
        {  //assert(capacity);
           delete[] data;
        }
     }

     /////////COMMANDS///////////////////
     //empty(): Test whether the set is empty
     bool empty() const { return current_size == 0; }
     //size:    Return the current_size of the Deque
     int size()        const{ return current_size; }
     //capacity:Return the capacity_size of the Deque
     int capacity()    const{ return capacity_size; }
     //clear:   Removes all items from Deque
	 void clear()
	 { 
		frontSpot = -1;
		backSpot = -1; 
		current_size = 0; 
	 }

     Deque<T> & operator = (const Deque<T> & rhs) throw (bad_alloc);

     //from 0 to 10 items
     //push_front():  Adds an item to the front/bottom of the Deque. //0///
     void push_front(const T & item);
     //push_back():  Adds an item to the back/top of the Deque       //10//
     void push_back(const T & item);

     //front(): Returns the item currently at the bottom/front of the Deque
     T & front()  throw(const char *);
     //back():  Returns the item currently at the top/back of the Deque
     T & back()   throw(const char *);

     //pop(): Removes an item from the front/bottom of the Deque   //0///
     void pop_front()   throw(const char *);
     //pop(): Removes an item from the back/top of the Deque       //10//
	 void pop_back()   throw(const char *);
};

/**********************************************************************
 * (1)//creating the steps for resizing the Deque
 ***********************************************************************/
template <class T>
void Deque<T> ::resize(int newCapacity) throw (bad_alloc)
{
   //allocate new array
   T * pNew;
   pNew = new T[newCapacity];
   //This will copy everything starting from the back of the array (frontSpot) until the frontish of the array (backSpot)
   //Note: this only works because current_size has not been changed yet
   if (current_size > 0)
   {
	   bool firstTime = true; // The logic in the for loops could possibly give bad results if this is the first time through.  If this is first time through loop, we want to run no matter what.
	   for (int i = frontSpot; (i != backSpot + 1 || firstTime); i++)
	   {
		   if (i == capacity_size)
		   {
			   i = -1;
		   }
		   else
		   {
			   pNew[i + capacity_size] = data[i]; //Put at back
		   }
		   firstTime = false;
	   }
	   frontSpot = frontSpot + capacity_size;
   }
   //delete old and assign the new
   delete[] data;
   data = pNew;
   capacity_size = newCapacity;
}

/**********************************************************************
 * (2)Deque-push_front
 *  -Adds an item to the front/bottom of the stack. //0//
 ***********************************************************************/
template <class T>
void Deque<T> ::push_front(const T & item)
{
	//cout << "current_size: " << current_size << "; capacity_size: " << capacity_size << "; frontSpot: " << frontSpot << "; backSpot: " << backSpot << "\n";
	//First resize, let's allocate default 1's
   if (current_size == 0 && capacity_size == 0)
   {
      //both barriers start at 0 and converted to 1
      capacity_size = 1;
      resize(1);
   }
   else if (((capacity_size - current_size) == 0) && (capacity_size != 0))
   {
	   resize(capacity_size * 2);
   }
   else if (frontSpot <= 0) //At the beginning, let's loop towards the back of the array
   {
	   frontSpot = capacity_size;
   }

    data[--frontSpot] = item;
	current_size++;
}

/**********************************************************************
 * (2)Deque-push_back
 *  -Adds an item to the top/back of the stack.  //10//
 ***********************************************************************/
template <class T>
void Deque<T> ::push_back(const T & item)
{ 
	//cout << "current_size: " << current_size << "; capacity_size: " << capacity_size << "; frontSpot: " << frontSpot << "; backSpot: " << backSpot << "\n";
	//First resize, let's allocate default 1's
	if (current_size == 0 && capacity_size == 0)
	{
		//both barriers start at 0 and converted to 1
		resize(1);
	}
	else if (((capacity_size - current_size) == 0) && (capacity_size != 0))
	{
		resize(capacity_size * 2);
	}
	else if (backSpot >= (capacity_size - 1)) //At the beginning, let's loop towards the back of the array
	{
		backSpot = -1;
	}

	data[++backSpot] = item;
	current_size++;
	//cout << "Inserted";
}

/**********************************************************************
 * (4)Deque-front
 *  -Returns the item currently at the front/bottom of the Deque.
 ***********************************************************************/
template <class T>
T & Deque<T> ::front()throw(const char *)
{
	//cout << "current_size: " << current_size << "; capacity_size: " << capacity_size << "; frontSpot: " << frontSpot << "; backSpot: " << backSpot << "\n";
	int tempFrontSpot;
	if (frontSpot == -1)
	{
		tempFrontSpot = 0;
	}
	else
	{
		tempFrontSpot = frontSpot;
	}
   if (!empty())
   {
	   return data[tempFrontSpot];
   }
   else
   {
      throw "ERROR: attempting to access an item in an empty Deque";
   }
}

/**********************************************************************
 * (3)Deque-back
 *  -Returns the item currently at the back/top of the stack.
 ***********************************************************************/
template <class T>
T & Deque<T> ::back()throw(const char *)
{
	//cout << "current_size: " << current_size << "; capacity_size: " << capacity_size << "; frontSpot: " << frontSpot << "; backSpot: " << backSpot << "\n";
	int tempBackSpot;
	if (frontSpot == capacity_size)
	{
		tempBackSpot = capacity_size - 1;
	}
	else
	{
		tempBackSpot = backSpot;
	}
	if (!empty())
	{
		return data[tempBackSpot];
	}
   else
   {
      throw "ERROR: attempting to access an item in an empty Deque";
   }
}

/**********************************************************************
* (5)Stack-pop
*  -Removes the item from the head
***********************************************************************/
template <class T>
void Deque<T> ::pop_front() throw(const char *)
{
	//cout << "current_size: " << current_size << "; capacity_size: " << capacity_size << "; frontSpot: " << frontSpot << "; backSpot: " << backSpot << "\n";
	if (!empty())
	{
		if (frontSpot == capacity_size - 1)
		{
			frontSpot = 0;
		}
		else
		{
			frontSpot++;
		}
		current_size--;
	}
	else
	{
		//if the stack is already empty, the
		//following c-string exception will be thrown:
		throw "ERROR: attempting to pop from an empty Deque";
	}
}

/**********************************************************************
* (5)Stack-pop
*  -Removes the item from the tail
***********************************************************************/
template <class T>
void Deque<T> ::pop_back() throw(const char *)
{
	//cout << "current_size: " << current_size << "; capacity_size: " << capacity_size << "; frontSpot: " << frontSpot << "; backSpot: " << backSpot << "\n";
	if (!empty())
	{
		if (backSpot == 0)
		{
			backSpot = capacity_size;
		}
		else
		{
			backSpot--;
		}
		current_size--;
	}
	else
	{
		//if the stack is already empty, the
		//following c-string exception will be thrown:
		throw "ERROR: attempting to pop from an empty Deque";
	}
}

/**********************************************************************
 * Deque-operator equals
 * //creating the steps for equaling the Deque
 ***********************************************************************/
template <class T>
Deque<T> & Deque<T> :: operator = (const Deque<T> & rhs) throw (bad_alloc)
{
   resize(rhs.current_size);

   //copy the data from the other size
   current_size = rhs.current_size;
   for (int i = 0; i < rhs.current_size; i++)
   {
      data[i] = rhs.data[i];
   }
   //return itself
   return *this;
}

#endif
