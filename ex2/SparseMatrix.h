/**
* SparseMatrix.h
*
* -------------------------------------------------------------------------------------------------
* General:		This class  represents sparse matrix
*				the matrix contain less than half are zero, stored in a map.
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
#include "Map.h"

#ifndef EPSLON
#define EPSLON 0.000001
#endif

using namespace std;

#ifndef _SPARSE_METRIX_H_
#define _SPARSE_METRIX_H_

/**
* This class  represents sparse matrix
* the matrix contain less than half are zero, stored in a map.
*/
class SparseMatrix : public Matrix
{
public:
	/**
	* class constructor
	* create a new colSizeXrowSize sparse matrix from the values in arr
	*/
	SparseMatrix(double arr[], unsigned int colSize, unsigned int rowSize);
	/**
	* copy constructor
	*/
	SparseMatrix(const SparseMatrix& other);
	/**
	* class desstructor
	*/
	virtual ~SparseMatrix();
	/**
	* copy the matrix and return the copy
	*/
	SparseMatrix* copyInto();
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
	Map _matrix;

	//for the iterator
	Map::iterator iter;
	unsigned int iterRow;
	unsigned int iterCol;

	// double pointer to 0. use for the iterator for element of 0
	double empty = 0;
	double* emptySlot = &empty;
};
#endif