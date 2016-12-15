/**
* MyMatrix.h
*
* -------------------------------------------------------------------------------------------------
* General:		This class represents a matrix and can operate thing such as M+N, M*N, M==n
*				and more.
*				The matrix can be in 2 different way. regular and sparse.
*				regular - more or equal to half of the values are nor zero, contained in a vector
*				sparse - less than half are zero, contained in a map.
*
* MyMatrix			- class constructor
*					  create a new colSizeXrowSize matrix from the values in arr
*
*					- copy constructor
*
*					- string constructor
*					  create a matrix from the givan string
*
* newMatrix			- create a colSizeXrowSize matrix from the values in arr
*
* ~MyMatrix			- class destructor
*
* operator=			- assign the other matrix into this
*
* operator<<		- ostream for the givan matrix
*
* operator+			- add this matrix with the other one and return the new matrix
*
* operator+=		- add this matrix the other one
*
* operator-(unary)	- return matrix with the opposite sign of every value in the matrix
*
* operator-			- decrease the other matrix from this one and return the new matrix
*
* operator-=		- and return the new matrix
*
* operator*			- multiply this matrix with the other one and return the new matrix
*
* operator*=		- multiply this matrix with the other one
*
* operator==		- return true iff all values are equals
*
* trace				- return the trace of the matrix. 0 if the matrix is not a square
*					  trace - the sum of the diagonal values
*
* frobeniusNorm		- return the frobenius norm of the matrix
*					  frobenius norm - sum of the matrix values square
*
* isEmpty			- return true if all values are zero
*
* getMatrix			- return the matrix
*
* setMatrix			- set the matrix
*
* getZero			- return the zero counter
*
* setZero			- set the zero counter
*
* incZero			- increase the zero counter by 1
*
* decZero			- decrease the zero counter by 1
*
* getRow			- return the row
*
* setRow			- set the row
*
* getCol			- return the column
*	
* setCol			- set the column
*
*
* switching between matrix kinds.
*	the way I implement the files, mostly for my own ease, most of the method are returning a new
*	matrix created *after* the operation goes. which mean the matrix already created in the right
*	form so there is no reason to switch anything.
* -------------------------------------------------------------------------------------------------
*/
#include "Matrix.h"
#include "RegMatrix.h"
#include "SparseMatrix.h"
#include <string>
#include <iomanip>
#include "Map.h"

#ifndef EPSLON
#define EPSLON 0.000001
#endif
#ifndef PRECISON
#define PRECISON 6
#endif
#ifndef EMPTY_MAT
#define EMPTY_MAT "0\n"
#endif
#ifndef COMMA
#define COMMA " , "
#endif
#ifndef NEW_LINE
#define NEW_LINE "\n"
#endif

using namespace std;

#ifndef _MY_METRIX_H_
#define _MY_METRIX_H_
/**
* This class represents a matrix and can operate thing such as M + N, M*N, M == n
* and more.
* The matrix can be in 2 different way.regular and sparse.
* regular - more or equal to half of the values are nor zero, contained in a vector
* sparse - less than half are zero, contained in a map.
*/
class MyMatrix
{
public:
	/**
	* class constructor
	* create a new colSizeXrowSize matrix from the values in arr
	*/
	MyMatrix(double arr[], unsigned int colSize, unsigned int rowSize);
	/**
	* copy constructor
	*/
	MyMatrix(const MyMatrix& other);
	/**
	* string constructor
	* create a matrix from the givan string
	*/
	MyMatrix(const string matrix);
	/**
	* create a colSizeXrowSize matrix from the values in arr
	* the method calculate the zero-valus sum then decide which matrix to create
	*/
	void newMatrix(double arr[], unsigned int colSize, unsigned int rowSize);
	/**
	* class destructor
	*/
	virtual ~MyMatrix();

	/**
	* assign the other matrix into this
	*/
	MyMatrix* operator=(const MyMatrix& other);


	/**
	* add this matrix with the other one and return the new matrix
	*/
	MyMatrix operator+(const MyMatrix& other) const; 

	/**
	* add this matrix the other one
	*/
	MyMatrix operator+=(const MyMatrix& other);

	/**
	* return matrix with the opposite sign of every value in the matrix
	*/
	MyMatrix operator-() const;

	/**
	* decrease the other matrix from this one and return the new matrix
	*/
	MyMatrix operator-(const MyMatrix& other) const;

	/**
	* and return the new matrix
	*/
	MyMatrix operator-=(const MyMatrix& other);

	/**
	* multiply this matrix with the other one and return the new matrix
	*/
	MyMatrix operator*(const MyMatrix& other) const;

	/**
	* multiply this matrix with the other one
	*/
	MyMatrix operator*=(const MyMatrix& other);

	/**
	* return true iff all values are equals
	*/
	bool operator==(const MyMatrix& other) const;

	/**
	* return the trace of the matrix. 0 if the matrix is not a square
	*
	* trace - the sum of the diagonal values
	*/
	double trace() const;

	/**
	* return the frobenius norm of the matrix
	*
	* frobenius norm - sum of the matrix values square
	*/
	double frobeniusNorm() const;

	/**
	* ostream for the givan matrix
	*/
	friend ostream& operator<<(ostream& os, const MyMatrix& matrix);

	/**
	* return true if all values are zero
	*/
	bool isEmpty() const;

	/**
	* return the matrix
	*/
	Matrix* getMatrix() const
	{
		return _matrix;
	}
	/**
	* set the matrix
	*/
	void setMatrix(Matrix* other)
	{
		_matrix = other;
	}
	/**
	* return the zero counter
	*/
	unsigned int getZero() const
	{
		return _zeroSum;
	}
	/**
	* set the zero counter
	*/
	void setZero(unsigned int other)
	{
		_zeroSum = other;
	}
	/**
	* increase the zero counter by 1
	*/
	void incZero()
	{
		_zeroSum++;
	}
	/**
	* decrease the zero counter by 1
	*/
	void decZero()
	{
		_zeroSum--;
	}
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
	Matrix* _matrix;
	unsigned int _zeroSum;
	unsigned int _row;
	unsigned int _col;

};
#endif