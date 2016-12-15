/**
* RegMatrix.h
*
* ------------------------------------------------------------------------------------------------ -
* General:		This class  represents regular matrix
*				the matrix contain more or equal than half zero, stored in a vector.
*
* MyMatrix			- class constructor
*					  create a new colSizeXrowSize sparse matrix from the values in arr
*
*					- copy constructor
*
* ~Matrix			- class destructor
*
* copyInto			- copy the matrix and return the copy
*
*~~~~~~~~~~~~~~~~~~~~~~~~~
* my iterator:
*		in order to be able to iterete on both matrix kind I spand many hours to create
*		this (kind of) iterator.
*		I didn't succeed to make it a different class and couldn't spent more time on it.
*		The iterator use class member to store the current iterator(of the real iterator)
*		and current row and column. Therefore only 1 iteretor can use at a time (what make a prablem
*		with operator+ as mention there)
*		every method have a boolen parameter "onlyNotZero" that is false by default.
*		In case it get "true", the sparse iteretor will run only on non-zero element.
*
* getFirst			- reset the iterator and return pointer to the first element
*
* hasNext			- return true iff there next element
*
* next				- increase the iterator and return the next element
*~~~~~~~~~~~~~~~~~~~~~~~~~
*
* getElem			- return the element in the (row, col) location
*
* -------------------------------------------------------------------------------------------------
*/
#include "Matrix.h"
#include "Vector.h"
#include "Map.h"


using namespace std;

#ifndef _REG_METRIX_H_
#define _REG_METRIX_H_

/**
* This class  represents regular matrix
* the matrix contain more or equal than half zero, stored in a vector.
*/
class RegMatrix : public Matrix
{
public:
	/**
	* class constructor
	* create a new colSizeXrowSize regular matrix from the values in arr
	*/
	RegMatrix(double arr[], unsigned int colSize, unsigned int rowSize);
	/**
	* copy constructor
	*/
	RegMatrix(const RegMatrix& other);
	/**
	* class desstructor
	*/
	~RegMatrix();

	/**
	* copy the matrix and return the copy
	*/
	RegMatrix* copyInto();
	/**
	* reset the iterator and return pointer to the first element
	*/
	virtual double* getFirst(bool onlyNotZero = false);
	/**
	*	return true iff there next element
	*/
	virtual bool hasNext(bool onlyNotZero = false);
	/**
	* increase the iterator and return the next element
	*/
	virtual double* next(bool onlyNotZero = false);
	/**
	* return the element in the (row, col) location
	*/
	double getElem(const unsigned int row, const unsigned int col) const;

private:
	Vector _matrix;

	//for the iterator
	Vector::iterator iter;
};
#endif
