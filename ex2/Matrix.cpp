/**
* Matrix.cpp
*
* -------------------------------------------------------------------------------------------------
* General:		This class is an abstract class represents the acuall matrix variable
*				The matrix can be in 2 different way. regular and sparse.
*				regular - more or equal to half of the values are nor zero, contained in a vector
*				sparse - less than half are zero, contained in a map.
* -------------------------------------------------------------------------------------------------
*/
#include <iterator>
#include "Matrix.h"
#include "Vector.h"

using namespace std;

Matrix::Matrix(unsigned int colSize, unsigned int rowSize)
{
	setRow(rowSize);
	setCol(colSize);
}

Matrix::Matrix(const Matrix& other)
{
	setRow(other.getRow());
	setCol(other.getCol());
}

Matrix::~Matrix()
{
	_row = 0;
	_col = 0;
}