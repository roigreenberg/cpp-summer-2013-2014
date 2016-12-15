/**
* RegMatrix.cpp
*
* -------------------------------------------------------------------------------------------------
* General:		This class  represents regular matrix
*				the matrix contain more or equal than half zero, stored in a vector.
* -------------------------------------------------------------------------------------------------
*/
#include <iterator>
#include "Vector.h"
#include "RegMatrix.h"

using namespace std;

RegMatrix::RegMatrix(double arr[], unsigned int colSize, unsigned int rowSize):
Matrix(colSize, rowSize)
{
	for (unsigned int r = 0; r < rowSize; r++)
	{
		for (unsigned int c = 0; c < colSize; c++)
		{
			_matrix.push_back(*(arr + c*rowSize + r));
		}
	}
}

RegMatrix::RegMatrix(const RegMatrix& other) : Matrix(other)
{
	setRow(other.getRow());
	setCol(other.getCol());
	_matrix = other._matrix;
}

RegMatrix::~RegMatrix()
{
	_matrix.clear();
}
RegMatrix* RegMatrix::copyInto()
{
	RegMatrix* temp = new RegMatrix(*this);
	return temp;
}

double RegMatrix::getElem(const unsigned int row, const unsigned int col) const
{
	return _matrix[row*getCol() + col];
}
double* RegMatrix::getFirst(bool onlyNotZero)
{
	iter = _matrix.begin();
	return &(*iter++);
}

bool RegMatrix::hasNext(bool onlyNotZero)
{
	return iter != _matrix.end();
}
double* RegMatrix::next(bool onlyNotZero)
{
	return &(*iter++);
}
