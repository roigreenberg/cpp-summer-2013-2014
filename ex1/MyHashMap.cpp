#include <iostream>
#include <math.h>
#include <string>
#include "MyHashMap.h"


#define EPS 0.000007

using namespace std;

/**
* The hash function.
* Input parameter - any C++ string.
* Return value: the hash value - the sum of all the characters of the string
*   (according to their ASCII value) modulus HASH_SIZE. The hash value of the
*   empty string is 0 (since there are no characters, their sum according to
*   the ASCII value is 0).
* NOTE: In a better design the function would have belong to the string class
*	 (or to a class that is derived from std::string). We implement it as a "stand
*	 alone" function since you didn't learn inheritance yet. Keep the function
*	 global (it's important to the automatic tests).
*/
int MyHashMap::myHashFunction(const std::string &str)
{
	int hash = 0;
	for (unsigned int i = 0; i < str.length(); i++)
	{
		hash += str[i];
	}
	return hash % HASH_SIZE;
}

/**
* Class constructor
*/
MyHashMap::MyHashMap()
{
	_size = 0;
}

/**
* Copy constructor
*/
MyHashMap::MyHashMap(const MyHashMap& h1)
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		_hashT[i] = h1._hashT[i];
	}
		_size = h1._size;

}

//MyHashMap& MyHashMap::operator=(const MyHashMap& h1)
//{
//	for (int i = 0; i < HASH_SIZE; i++)
//	{
//		_hashT[i] = h1._hashT[i];
//	}
//	_size = h1._size;
//	return *this;
//}


/**
* Class destructor
*/
MyHashMap::~MyHashMap()
{

	//cout << "^^^^^^^^^^^^^^^^^^^^^^^" << endl;
	//cout << MyLinkedList::b() << "-" << MyLinkedList::a() << endl;
}

/**
* add a string to the HashMap. Locate the entry of the relevant linked list in
* the HashMap using the function myHashFunction, and add the element to the end of that list.
* If the element already exists in the HashMap, change its data to the
* input parameter. Important: unlike our MyLinkedList, that HashMap will contain at most
* one copy of each std::string.
*/
void MyHashMap::add(const std::string &str, double data)
{
	int hash = myHashFunction(str);
	if (isInHashMap(str) == false)
	{
		_hashT[hash].add(str, data);
		_size++;
	}
	else
	{
		_hashT[hash].remove(str);
		_hashT[hash].add(str, data);
	}

}

/**
* remove a string from the HashMap. Locate the entry of the relevant linked list in
* the HashMap using the function myHashFunction, and remove the element from it.
* Return one on success, or zero if the element wasn't in the HashMap.
*/
size_t MyHashMap::remove(const std::string &str)
{
	int result = _hashT[myHashFunction(str)].remove(str);
	_size -= result;
	return result;
}

/**
* Return true if the element is in the HashMap, or false otherwise.
* If the element exists in the hash map, return in 'data' its appropriate data
* value. Otherwise don't change the value of 'data'.
*/
bool MyHashMap::isInHashMap(const std::string &str, double &data) const
{
	return _hashT[myHashFunction(str)].isInList(str, data);
}

/**
* Return number of elements stored in the HashMap
*/
int MyHashMap::size() const
{
	return _size;
}

/**
* Return true if and only if there exists a string that belong both to the
* HashMap h1 and to this HashMap
*/
bool MyHashMap::isIntersect(const MyHashMap &h1) const
{
	//MyLinkedListNode* node;
	for (int i = 0; i < HASH_SIZE; i++)
	{
		/*node = _hashT[i]._head;
		while (node != NULL)
		{
			if (h1.isInHashMap(_hashT[i].getKey(node)))
			{
				return true;
			}
			node = _hashT[i].getNext(node);
		}*/
		if (_hashT[i].isIntersect(h1._hashT[i]))
		{
			return true;
		}
	}
	
	return false;
}

/**
* Return the total wight of the hash elements
*/
double MyHashMap::totWeight() const
{
	double weight = 0;
	for (int i = 0; i < HASH_SIZE; i++)
	{
		weight += _hashT[i].sumList();
	}
	return weight;
}

/**
* Return true is totWeight is equal to h1 totWeight
*/
bool MyHashMap::operator==(const MyHashMap& h1)
{
	return fabs(totWeight() - h1.totWeight()) < EPS;
}

/**
* Return true is totWeight is smaller then h1 totWeight
*/
bool MyHashMap::operator<(const MyHashMap& h1)
{
	return totWeight() - h1.totWeight() < EPS;
}

/**
* Return true is totWeight is bigger then h1 totWeight
*/
bool MyHashMap::operator>(const MyHashMap& h1)
{
	return totWeight() - h1.totWeight() > EPS;
}

/**
* Minus operation
* return new HashMAp contain the element from left HaspMap that doesn't appear in the right one
*/
MyHashMap MyHashMap::operator-(const MyHashMap& h1)
{
	MyHashMap minus;

	for (int i = 0; i < HASH_SIZE; i++)
	{
		minus._hashT[i] = _hashT[i] - h1._hashT[i];
		minus._size += minus._hashT[i].lengthList();
	}
	return minus;
}

/**
* Union operation
* return new HashMAp contain the element from both HashMaps.
* in case of duplicate only the element from the left HashMap will be saved.
*/
MyHashMap MyHashMap::operator|(const MyHashMap& h1)
{
	//MyHashMap* uniun = new MyHashMap(*this);
	MyHashMap uniun;
	//MyLinkedListNode* node;
	for (int i = 0; i < HASH_SIZE; i++)
	{
	/*	node = h1._hashT[i]._head;
		while (node != NULL)
		{
			if (!isInHashMap(_hashT[i].getKey(node)))
			{
				uniun.add(_hashT[i].getKey(node), _hashT[i].getData(node));
			}
			node = h1._hashT[i].getNext(node);*/
		//}
		uniun._hashT[i] = _hashT[i] | h1._hashT[i];
		uniun._size += uniun._hashT[i].lengthList();
	}

	return uniun;
}

/**
* Intersection operation
* return new HashMAp contain only the element appear in both HashMaps.
* the data of the element from the left HashMap will be saved.
*/
MyHashMap MyHashMap::operator&(const MyHashMap& h1)
{
	MyHashMap inter;
	//MyLinkedListNode* node;
	for (int i = 0; i < HASH_SIZE; i++)
	{
		/*node = _hashT[i]._head;
		while (node != NULL)
		{
			if (h1.isInHashMap(_hashT[i].getKey(node)))
			{
				inter.add(_hashT[i].getKey(node), _hashT[i].getData(node));
			}
			node = _hashT[i].getNext(node);
		}*/
		inter._hashT[i] = _hashT[i] & h1._hashT[i];
		inter._size += inter._hashT[i].lengthList();
	}
	//delete(node);
	return inter;
}

void MyHashMap::print() const
{
	for (int i = 0; i < HASH_SIZE; i++)
	{
		if (_hashT[i].sumList() != 0)
		{
			cout << "*** " << i << " ***" << endl;
			_hashT[i].printList();
		}
	}
}
