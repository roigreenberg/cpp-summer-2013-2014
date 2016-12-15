/**
* MyLinkedList.h
*
* ---------------------------------------------------------------------------------------------------------------
* General: This class represents a Linkedlist, a data structure that every node point to the next and prev nodes
*
*  Methods: 
*  MyLinkedList()		- Constructor
*  ~MyLinkedList()      - Destructor
*
*  add                  - Add a string to the LinkedList
*
*  remove               - Remove all element of string from the list
*
*  isInList	            - Return true if the element is in the LinkedList, or false otherwise.
*                         If the element exists in the HashMap, return in 'data' its appropriate data
*                         value. Otherwise don't change the value of 'data'.
*
*  printList			- print the list
*
*  sumList	            - Return the total weight of the hash elements
*
*  getNext				- Return the node next
*
*  getKey				- Return the node key
*
*  getData				- Return the node data
*
*  operator=			- copy the right list into the left one
*
* --------------------------------------------------------------------------------------
*/
#include <string>

#include <iostream>

using namespace std;

#ifndef _MYLINKEDLIST_H_
#define _MYLINKEDLIST_H_

class MyLinkedListNode;

// static double for default parameter for isInList
static double d;
//
//static int d0 = 0;
//static int n = 0;

/**
* The definition of the LinkedList
*/
class MyLinkedList
{
public:
	static void a(){ /*cout << "D:" << ++d0 << endl;*/ }
	static void b(){ /*cout << "N:" << ++n << endl;*/ }
	/**
	* Class constructor
	*/
	MyLinkedList();

	/**
	* Class disstructor
	*/
	~MyLinkedList();

	/**
	* Add a string to the LinkedLis
	*/
	void add(const string key, const double data);

	/**
	* Remove all element with the same key from the list
	*/
	int remove(const string key);

	/**
	* Return true if the element is in the LinkedList, or false otherwise.
	* If the element exists in the HashMap, return in 'data' its appropriate data
	* value. Otherwise don't change the value of 'data'.
	*/
	bool isInList(const string key, double& data = d) const;

	/**
	* print the list
	*/
	void printList() const;

	/**
	* Return the total weight of the list
	*/
	double sumList() const;

	/**
	* Return the size of the list
	*/
	int lengthList() const;

	///**
	//* Return the node next
	//*/
	//MyLinkedListNode* getNext(MyLinkedListNode* node) const;

	///**
	//* Return the node key
	//*/
	//string& getKey(MyLinkedListNode* node) const;

	///**
	//* Return the node data
	//*/
	//double& getData(MyLinkedListNode* node) const;

	/**
	* Return true if and only if there exists a string that belong both to the
	* HashMap h1 and to this HashMap
	*/
	bool isIntersect(const MyLinkedList &h1) const;

	/**
	* copy the right list into the left one
	*/
	MyLinkedList& operator=(const MyLinkedList&);

	/**
	* Minus operation
	* return new LinkedList contain the element from left LinkedList that doesn't appear in the right one
	*/
	MyLinkedList operator-(const MyLinkedList& l1);

	/**
	* Union operation
	* return new LinkedList contain the element from both LinkedList.
	* in case of duplicate only the element from the left LinkedList will be saved.
	*/
	MyLinkedList operator|(const MyLinkedList& l1);

	/**
	* Intersection operation
	* return new LinkedList contain only the element appear in both LinkedList.
	* the data of the element from the left LinkedList will be saved.
	*/
	MyLinkedList operator&(const MyLinkedList& l1);

	MyLinkedListNode* _head;
private:
	/**
	* helper method.
	* remove the spesific node from the list
	*/
	void removeNode(MyLinkedListNode* nodeToRemove);
	double _sum;
	int _length;
	MyLinkedListNode* _tail;
};
#endif