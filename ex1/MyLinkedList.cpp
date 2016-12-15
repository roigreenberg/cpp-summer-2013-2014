#include "MyLinkedList.h"
#include <iostream>
#include <string>


using namespace std;


class MyLinkedListNode
{
public:
	MyLinkedListNode(const string key, const double data);
	~MyLinkedListNode(){ MyLinkedList::a(); /*cout << "@@@" << _key << endl;*/ }
	MyLinkedListNode* getNext();
	MyLinkedListNode* getPrev();
	void setNext(MyLinkedListNode* next);
	void setPrev(MyLinkedListNode* prev);
	double& getData();
	string& getKey();
	
private:
	
	double _data;
	string _key;
	MyLinkedListNode* _next;
	MyLinkedListNode* _prev;

};

MyLinkedListNode::MyLinkedListNode(const string key, const double data)
{
	MyLinkedList::b();
	_key = key;
	_data = data;
	_next = NULL;
	_prev = NULL;
}


MyLinkedListNode* MyLinkedListNode::getNext()
{
	return _next;
}
MyLinkedListNode* MyLinkedListNode::getPrev()
{
	return _prev;
}
void MyLinkedListNode::setNext(MyLinkedListNode* next)
{
	_next = next;
	if (_next != NULL)
	{
		next->_prev = this;
	}
}
void MyLinkedListNode::setPrev(MyLinkedListNode* prev)
{
	_prev = prev;
	if (prev != NULL)
	{
		prev->_next = this;
	}
}
double& MyLinkedListNode::getData()
{
	return _data;
}
string& MyLinkedListNode::getKey()
{
	return _key;
}

MyLinkedList::MyLinkedList()
{
	_head = NULL;
	_tail = NULL;
	_length = 0;
	_sum = 0;
}

MyLinkedList::~MyLinkedList()
{
	MyLinkedListNode* node = _head;
	while (_head != NULL)
	{

		removeNode(_head);
		node = node->getNext();

	}
	//delete(node);
}

void MyLinkedList::add(const string key, const double data)
{
	MyLinkedListNode* newNode = new MyLinkedListNode(key, data);
	if (_head == NULL)
	{
		_head = newNode;

	}
	else
	{
		_tail->setNext(newNode);
	}
	_tail = newNode;
	_length++;
	_sum += data;
}

void MyLinkedList::removeNode(MyLinkedListNode* nodeToRemove)
{
	MyLinkedListNode* node = nodeToRemove;
	_sum -= node->getData();
	if (node == _head)
	{
		if (_head == _tail)
		{
			_head = NULL;
			_tail = NULL;
			delete(node);
			return;
		}
		_head = node->getNext();
	}
	else
	{
		node->getPrev()->setNext(node->getNext());
	}
	if (node == _tail)
	{
		_tail = node->getPrev();
	}
	else
	{
		node->getNext()->setPrev(node->getPrev());
	}
	delete(node);
}

int MyLinkedList::remove(const string key)
{
	MyLinkedListNode* node = _head;
	int num = 0;
	while (node != NULL)
	{

		if (node->getKey() == key)
		{
			removeNode(node);
			num++;
		}
		node = node->getNext();

	}
	//delete(node);
	return num;

}

bool MyLinkedList::isInList(const string key, double& data) const
{
	MyLinkedListNode* node = _head;
	while (node != NULL)
	{

		if (node->getKey() == key)
		{
			data = node->getData();
			return true;
		}
		node = node->getNext();

	}
	//delete(node);
	return false;
}

void MyLinkedList::printList() const
{
	if (_head == NULL)
	{
		cout << "Empty" << endl;
		return;
	}
	MyLinkedListNode* node = _head;
	while (node != NULL)
	{

		cout << node->getKey() << "," << node->getData() << endl;
		node = node->getNext();

	}
	//delete(node);
}

double MyLinkedList::sumList() const
{
	return _sum;
}

/**
* Return the size of the list
*/
int MyLinkedList::lengthList() const
{
	return _length;
}

//MyLinkedListNode* MyLinkedList::getNext(MyLinkedListNode* node) const
//{
//	return node->getNext();
//}
//
//string& MyLinkedList::getKey(MyLinkedListNode* node) const
//{
//	return node->getKey();
//}
//
//double& MyLinkedList::getData(MyLinkedListNode* node) const
//{
//	return node->getData();
//}

/**
* Return true if and only if there exists a string that belong both to the
* HashMap h1 and to this HashMap
*/
bool MyLinkedList::isIntersect(const MyLinkedList &l1) const
{
	MyLinkedListNode* node;

	node = _head;
	while (node != NULL)
	{
		if (l1.isInList(node->getKey()))
		{
			return true;
		}
		node = node->getNext();
	}


	return false;
}

MyLinkedList& MyLinkedList::operator=(const MyLinkedList& l1)
{
	MyLinkedListNode* node = l1._head;
	while (node != NULL)
	{
		add(node->getKey(), node->getData());
		node = node->getNext();
	}
	//delete(node);
	//cout << lengthList() << ":" << l1.lengthList() << endl;
	return *this;
}

/**
* Minus operation
* return new LinkedList contain the element from left LinkedList that doesn't appear in the right one
*/
MyLinkedList MyLinkedList::operator-(const MyLinkedList& l1)
{
	MyLinkedList list;
	MyLinkedListNode* node;
	node = _head;
	while (node != NULL)
	{
		if (!l1.isInList(node->getKey()))
		{
			list.add(node->getKey(), node->getData());
		}
		node = node->getNext();
	}
	//delete(node);
	return list;
}

/**
* Union operation
* return new LinkedList contain the element from both LinkedList.
* in case of duplicate only the element from the left LinkedList will be saved.
*/
MyLinkedList MyLinkedList::operator|(const MyLinkedList& l1)
{
	MyLinkedList list;
	list = *this;
	MyLinkedListNode* node;

		node = l1._head;
		while (node != NULL)
		{
			if (!isInList(node->getKey()))
			{
				list.add(node->getKey(), node->getData());
			}
			node = node->getNext();
		}
	//delete(node);
	return list;
}

/**
* Intersection operation
* return new LinkedList contain only the element appear in both LinkedList.
* the data of the element from the left LinkedList will be saved.
*/
MyLinkedList MyLinkedList::operator&(const MyLinkedList& l1)
{
	MyLinkedList list;
	MyLinkedListNode* node;

		node = _head;
		while (node != NULL)
		{
			if (l1.isInList(node->getKey()))
			{
				list.add(node->getKey(), node->getData());
			}
			node = node->getNext();
		}

	//delete(node);
	return list;
}




#ifdef A
int main()
{
	/*MyLinkedListNode* head = new MyLinkedListNode("A", 1.0);
	head->setNext(new MyLinkedListNode("B", 2.0));
	head->getNext()->setNext(new MyLinkedListNode("C", 3.0));

	MyLinkedListNode* test = head;
	MyLinkedListNode* tail;
	while (test != NULL)
	{

	cout << test->getKey() << ", " << test->getData() << endl;
	_tail = test;
	test = test->getNext();

	}
	while (_tail != NULL)
	{

		cout << tail->getKey() << ", " << tail->getData() << endl;
		test = tail;
		tail = tail->getPrev();

	}*/

	MyLinkedList l;

	l.add("A", 1);
	l.add("B", 2);
	cout << "!" << endl;
	l.add("C", 3);
	l.add("A", 4);

	l.printList();
	cout << "sum = " << l.sumList() << endl;
	double a = 0;
	cout << "search Q = " << l.isInList("Q", a) << endl;
	cout << "a= " << a << endl;
	cout << "search A = " << l.isInList("A", a) << endl;
	cout << "a= " << a << endl;
	MyLinkedList l2;
	l2 = l;
	cout << "L2" << endl;
	l2.printList();
	cout << "K= " << l.getKey(l._head) << endl;
	//cout << l->remove("A") << endl;
	cout << l.remove("B") << endl;
	cout << l.remove("C") << endl;
	cout << l.remove("A") << endl;
	cout << "search A = " << l2.isInList("A", a) << endl;
	cout << "a= " << a << endl;
	cout << "search B = " << l2.isInList("B", a) << endl;
	cout << "a= " << a << endl;
	cout << "search V = " << l2.isInList("V", a) << endl;
	cout << "a= " << a << endl;
	l.printList();
	return 0;
}
#endif
