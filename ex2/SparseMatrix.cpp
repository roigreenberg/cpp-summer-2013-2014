/**
* SparseMatrix.cpp
*
* -------------------------------------------------------------------------------------------------
* General:		This class  represents sparse matrix
*				the matrix contain less than half are zero, stored in a map.
* -------------------------------------------------------------------------------------------------
*/
#include <math.h>
#include "Map.h"
#include "SparseMatrix.h"

using namespace std;

SparseMatrix::SparseMatrix(double arr[], unsigned int colSize, unsigned int rowSize) :
Matrix(colSize, rowSize)
{
	Pair key;
	double val;
	for (unsigned int c = 0; c < colSize; c++)
	{
		key.second = c;
		for (unsigned int r = 0; r < rowSize; r++)
		{
			key.first = r;
			val = *arr++;
			if (fabs(val - 0) > EPSLON)
			{
				_matrix[key] = val;
			}
		}
	}
}

SparseMatrix::SparseMatrix(const SparseMatrix& other) : Matrix(other)
{
	setRow(other.getRow());
	setCol(other.getCol());
	_matrix = other._matrix;
}

SparseMatrix* SparseMatrix::copyInto()
{
	SparseMatrix* temp = new SparseMatrix(*this);
	return temp;
}

SparseMatrix::~SparseMatrix()
{
	_matrix.clear();
}

double* SparseMatrix::getFirst(bool onlyNotZero)
{
	iter = _matrix.begin();
	iterRow = 0;
	iterCol = 0;

	//in case of the zer matrix
	if (iter == _matrix.end())
	{
		return emptySlot;
	}

	if ((iter->first.first == iterRow && iter->first.second == iterCol) || onlyNotZero)
	{
		return &((*iter++).second);
	}
	else
	{
		return emptySlot;
	}
}

bool SparseMatrix::hasNext(bool onlyNotZero)
{
	if (onlyNotZero)
	{
		return iter != _matrix.end();
	}
	else
	{
		return (iterRow != getRow() - 1) || iterCol != getCol() - 1;
	}
}

double* SparseMatrix::next(bool onlyNotZero)
{

	if (iterCol == getCol() - 1)
	{
		iterCol = 0;
		iterRow++;
	}
	else
	{
		iterCol++;
	}
	if ((iter->first.first == iterRow && iter->first.second == iterCol && iter != _matrix.end())
		|| onlyNotZero)
	{
		return &(iter++)->second;
	}
	else
	{
		return emptySlot;
	}
}

double SparseMatrix::getElem(const unsigned int row, const unsigned int col) const
{
	Pair key(row, col);
	if (_matrix.find(key) == _matrix.end())
	{
		return 0;
	}
	return _matrix.at(key);
}





