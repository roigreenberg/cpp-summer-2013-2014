/**
* Matrix.h
*
* -------------------------------------------------------------------------------------------------
* General:		This class is an abstract class represents the acuall matrix variable
*				The matrix can be in 2 different way. regular and sparse.
*				regular - more or equal to half of the values are nor zero, contained in a vector
*				sparse - less than half are zero, contained in a map.
*
* MyMatrix			- class constructor
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
* getRow			- return the row
*
* setRow			- set the row
*
* getCol			- return the column
*
* setCol			- set the column
* -------------------------------------------------------------------------------------------------
*/
#include <string>
#include "Map.h"

using namespace std;

#ifndef _METRIX_H_
#define _METRIX_H_

/**
* This class is an abstract class represents the acuall matrix variable
* The matrix can be in 2 different way. regular and sparse.
* regular - more or equal to half of the values are nor zero, contained in a vector
* sparse - less than half are zero, contained in a map.
*/
class Matrix
{
public:
	/**
	* class constructor
	* set row and column
	*/
	Matrix(unsigned int colSize, unsigned int rowSize);
	/**
	* copy constructor
	*/
	Matrix(const Matrix& other);
	/**
	* class desstructor
	*/
	virtual ~Matrix();

	/**
	* copy the matrix and return the copy
	*
	* pure virtual method
	*/
	virtual Matrix* copyInto() = 0;
	/**
	* reset the iterator and return pointer to the first element
	*
	* pure virtual method
	*/
	virtual double* getFirst(bool onlyNotZero = false) = 0;
	/**
	*	return true iff there next element
	*
	* pure virtual method
	*/
	virtual bool hasNext(bool onlyNotZero = false) = 0;
	/**
	* increase the iterator and return the next element
	*
	* pure virtual method
	*/
	virtual double* next(bool onlyNotZero = false) = 0;
	/**
	* return the element in the (row, col) location
	*
	* pure virtual method
	*/
	virtual double getElem(const unsigned int row, const unsigned int col) const = 0;

	/**
	* return the row
	*/
	unsigned int getRow() const
	{
		return _row;
	}
	/**
	* set the row
	*/
	void setRow(unsigned int other)
	{
		_row = other;
	}
	/**
	* return the column
	*/
	unsigned int getCol() const
	{
		return _col;
	}
	/**
	* set the column
	*/
	void setCol(unsigned int other)
	{
		_col = other;
	}

private:
	unsigned int _row;
	unsigned int _col;

};
#endif