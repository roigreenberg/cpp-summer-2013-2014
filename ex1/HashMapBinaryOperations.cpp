#include <iostream>
#include <math.h>
#include <string>
#include "MyHashMap.h"

using namespace std;

#define SIZE  100

#ifndef EPS
#define EPS 0.000007
#endif

int main()
{
	MyHashMap h;
	MyHashMap h1;
	MyHashMap h2;

	cout << "\n---test operations---" << endl;

	h.add("", 4);
	h1.add("a", 0.2);
	h1.add("aa", 0.3);
	h1.add("aaa", 0.5);
	h1.add("b", 2.2);
	h1.add("bb", 2.3);
	h1.add("bbb", 2.5);
	h2.add("c", 4.2);
	h2.add("cc", 4.3);
	h2.add("ccc", 4.5);
	h2.add("a", 1.2);
	h2.add("aa", 1.3);
	h2.add("aaa", 1.5);

	MyHashMap h3 = h1 - h2;
	MyHashMap h4 = h1 | h2;
	MyHashMap h5 = h2 & h1;

	cout << "\ntest weight and size" << endl;
	if (fabs(h1.totWeight() - 8) > EPS)
	{
		cout << "h1  should be 8 not " << h1.totWeight() << endl;
	}
	if (h1.size() != 6)
	{
		cout << "h1 size should be 6 not " << h1.size() << endl;
	}
	if (fabs(h2.totWeight() - 17) > EPS)
	{
		cout << "h2 Weight should be 17 not " << h2.totWeight() << endl;
	}
	if (h2.size() != 6)
	{
		cout << "h2 size should be 2 not " << h2.size() << endl;
	}
	if (fabs(h3.totWeight() - 7) > EPS)
	{
		cout << "h3 Weight should be 7 not " << h3.totWeight() << endl;
	}
	if (h3.size() != 3)
	{
		cout << "h3 size should be 3 not " << h3.size() << endl;
	}
	if (fabs(h4.totWeight() - 21) > EPS)
	{
		cout << "h4 Weight should be 21 not " << h4.totWeight() << endl;
	}
	if (h4.size() != 9)
	{
		cout << "h4 size should be 9 not " << h4.size() << endl;
	}
	if (fabs(h5.totWeight() - 4) > EPS)
	{
		cout << "h5 Weight should be 4 not " << h5.totWeight() << endl;
	}
	if (h5.size() != 3)
	{
		cout << "h5 size should be 3 not " << h5.size() << endl;
	}
	cout << "	test end" << endl;


	cout << "\ntest operations < > ==" << endl;
	if (h2 < h1)
	{
		cout << "h2 should be bigger than h1" << endl;
	}
	if ((h3 > h4))
	{
		cout << "h4 should be bigger than h3" << endl;
	}
	if (!(h == h5))
	{
		cout << "h1 should be equal to h5" << endl;
	}
	if ((h2 == h4))
	{
		cout << "h2 shouldnt be equal to h4" << endl;
	}
	cout << "	test end" << endl;


	return 0;
}
