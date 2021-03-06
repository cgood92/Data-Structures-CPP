/***********************************************************************
* Program:
*    Lesson 8, Map
*    Brother Sloan, CS 235
* Author:
*      Clint Goodman and Parker Hubbard
* Summary:
************************************************************************/
#ifndef MAP_H
#define MAP_H

#include <cassert>
#include <iostream>
#include <string>
#include "pair.h"
#include "bst.h"
#include "bnode.h"
using namespace std;

template <class T1, class T2>
class MapIterator;
/**********************************************************************
* Map
***********************************************************************/
template <class T1, class T2>
class Map
{
private:
	BST < Pair<T1, T2> > * masterTree;
	int sizeInt;    //number of items currently on the map/tree
public:
	Map() : masterTree(NULL), sizeInt(0)
	{
	}
	~Map()
	{
	}
	Map(const Map <T1, T2> & rhs)
	{
		this->masterTree = new BST < Pair<T1, T2> >(*rhs.masterTree);
		this->sizeInt = rhs.sizeInt;
	}
	Map <T1, T2> & operator = (const Map <T1, T2> & rhs)
	{
		this->masterTree = new BST < Pair<T1, T2> >(*rhs.masterTree);
		this->sizeInt = rhs.sizeInt;
		return *this;
	}


	Pair<T1, T2> & operator [] (const T1 & key)
	{
		if (!masterTree)
		{
			masterTree = new BST < Pair<T1, T2> >();
		}
		//have the iterator point to where the key variable lies
		BSTIterator < Pair<T1, T2> > it = masterTree->find(Pair<T1, T2>(key, T2()));
		//if it does not currently point at the end() pointer
		if (it.stackOfNodes && it != masterTree->end())
		{
			return *it;
		}
		else
		{
			//otherwise insert that variable into the tree
			masterTree->insert(Pair<T1, T2>(key, T2()));
			it = masterTree->find(Pair<T1, T2>(key, T2()));
			sizeInt++;
			return *it;
		}
	}
	bool empty()
	{
		return (sizeInt == 0);
	}
	int size()
	{
		return sizeInt;
	}
	void clear()
	{
		this->masterTree->clear();
		sizeInt = 0;
	}
	MapIterator < T1, T2 > find(const T1 & key)
	{
		MapIterator < T1, T2 > it = this->begin();
		for (; it != this->end(); ++it)
			if (it.getKey() == key)
				return it;
		return MapIterator < T1, T2 >();
	}
	MapIterator < T1, T2 > begin()
	{
		if (this->masterTree)
		{
			return MapIterator < T1, T2 >(this->masterTree->begin());
		}
		else
		{
			return MapIterator < T1, T2 >();
		}
	}

	MapIterator < T1, T2 > end()
	{
		if (this->masterTree)
		{
			return MapIterator < T1, T2 >(this->masterTree->end());
		}
		else
		{
			return MapIterator < T1, T2 >();
		}
	}
	MapIterator < T1, T2 > rbegin()
	{
		if (this->masterTree)
		{
			return MapIterator < T1, T2 >(this->masterTree->rbegin());
		}
		else
		{
			return MapIterator < T1, T2 >();
		}
	}
	MapIterator < T1, T2 > rend()
	{
		if (this->masterTree)
		{
			return MapIterator < T1, T2 >(this->masterTree->rend());
		}
		else
		{
			return MapIterator < T1, T2 >();
		}
	}
};

/**********************************************************************
* MapIterator
***********************************************************************/
template <class T1, class T2>
class MapIterator
{
private:
	BSTIterator < Pair < T1, T2 > > masterTreeIt;
public:
	MapIterator()
	{
	}
	MapIterator(BSTIterator < Pair<T1, T2> > masterTreeIt)
	{
		this->masterTreeIt = masterTreeIt;
	}
	MapIterator(const MapIterator < T1, T2 > & rhs)
	{
	}
	MapIterator < T1, T2 > & operator = (const MapIterator < T1, T2 > & rhs)
	{
		masterTreeIt = rhs.masterTreeIt;
		return *this;
	}
	T2 & operator * ()
	{
		return (*masterTreeIt).second;
	}
	T1 & getKey()
	{
		return (*masterTreeIt).first;
	}
	bool operator != (const MapIterator < T1, T2 > & rhs) const
	{
		return masterTreeIt != rhs.masterTreeIt;
	}
	bool operator == (const MapIterator < T1, T2 > & rhs) const
	{
		return !(masterTreeIt != rhs.masterTreeIt);
	}
	MapIterator < T1, T2 > & operator -- ()
	{
		masterTreeIt--;
		return *this;
	}
	MapIterator < T1, T2 > operator--(int prefix)
	{
		MapIterator < T1, T2 > tmp(*this);
		masterTreeIt--;
		return tmp;
	}
	MapIterator < T1, T2 > & operator ++ ()
	{
		masterTreeIt++;
		return *this;
	}
	MapIterator < T1, T2 > operator++(int postfix)
	{
		MapIterator < T1, T2 > tmp(*this);
		masterTreeIt++;
		return tmp;
	}
};

#endif
