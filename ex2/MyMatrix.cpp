/**
* MyMatrix.cpp
*
* -------------------------------------------------------------------------------------------------
* General:		This class represents a matrix and can operate thing such as M+N, M*N, M==n
*				and more.
*				The matrix can be in 2 different way. regular and sparse.
*				regular - more or equal to half of the values are nor zero, contained in a vector
*				sparse - less than half are zero, contained in a map.
* -------------------------------------------------------------------------------------------------
*/
#include <sstream>
#include <math.h>
#include <iterator>
#include "MyMatrix.h"
#include "Vector.h"


using namespace std;

MyMatrix::MyMatrix(double arr[], unsigned int colSize, unsigned int rowSize) :
					_row(rowSize), _col(colSize)
{
	newMatrix(arr, colSize, rowSize);
}

MyMatrix::MyMatrix(const string other)
{
	string line, data;
	double* temp;
	char split_char = ',';
	unsigned int index;
	int row, col, curRow, curCol;
	istringstream split(other);

	row = 0;
	for (index = 0; index < other.length(); index++)
	{
		if (other[index] == '\n')
		{
			row++;
		}
	}
	col = 1;
	index = 0;
	while (other[index] != '\n')
	{
		index++;
		if (other[index] == ',')
		{
			col++;
		}
	}
	setRow(row);
	setCol(col);

	temp = new double[getRow()*getCol()];
	index = 0;
	curRow = 0;
	while (getline(split, line))
	{
		curCol = 0;
		istringstream split(line);
		while (getline(split, data, split_char))
		{
			(*(temp + curCol*getRow() + curRow)) = stod(data);
			curCol++;
		}
		curRow++;
	}
	newMatrix(temp, col, row);
	delete[] temp;
}

MyMatrix::MyMatrix(const MyMatrix& other)
{
	_row = other._matrix->getRow();
	_col = other._matrix->getCol();
	_zeroSum = other._zeroSum;
	setMatrix(other._matrix->copyInto());
}

/**
* create a colSizeXrowSize matrix from the values in arr
* the method calculate the zero-valus sum then decide which matrix to create
*/
void MyMatrix::newMatrix(double arr[], unsigned int colSize, unsigned int rowSize)
{
	setZero(0);
	int size = getRow()*getCol();
	for (int i = 0; i < size; i++)
	{
		if (fabs(arr[i] - 0) < EPSLON)
		{
			incZero();
		}
	}
	if ((float)getZero() / size <= 0.5)
	{
		setMatrix(new RegMatrix(arr, getCol(), getRow()));
	}
	else
	{
		setMatrix(new SparseMatrix(arr, getCol(), getRow()));
	}
}

MyMatrix::~MyMatrix()
{
	_row = 0;
	_col = 0;
	delete _matrix;
}
/**
* assign the other matrix into this
* the assignment create a new matrix of the type of other (no need to switch)
*/
MyMatrix* MyMatrix::operator=(const MyMatrix& other)
{
	if (this == &other)
	{
		return this;
	}
	setRow(other.getRow());
	setCol(other.getCol());
	delete _matrix;
	setMatrix(other.getMatrix()->copyInto());
	setZero(other.getZero());
	return this;
}

/**
* add this matrix with the other one and return the new matrix
*
* the method create an array of the new matrix to be then create a new matrix from it.
*
* due some implementetion difficulte i did it without the iterator
* (i couldn't run my iterator in case both matrix are acually the same)
*/
MyMatrix MyMatrix::operator+(const MyMatrix& other) const
{
	//in case one of the matrix is zero
	if (isEmpty())
	{
		return other;
	}
	if (other.isEmpty())
	{
		return *this;
	}

	double* tmpArr = new double[getRow() * getCol()]();

	for (unsigned int row = 0; row < getRow(); row++) 
	{
		for (unsigned int col = 0; col < getCol(); col++) 
		{
			tmpArr[getRow()*col + row] = 
				this->_matrix->getElem(row, col) + other._matrix->getElem(row, col);
		}
	}
	MyMatrix temp(tmpArr, getCol(), getRow());
	delete[] tmpArr;
	return temp;

}

MyMatrix MyMatrix::operator+=(const MyMatrix& other)
{
	*this = *this + other;
	return *this;
}

/**
* decrease the other matrix from this one and return the new matrix
*
* the method create a new matrix then change all sign.
*
* using my iterator method 
* in case of sparse matrix the iterator run only on non-zero values
*/
MyMatrix MyMatrix::operator-() const
{
	MyMatrix temp(*this);
	double* slot = temp.getMatrix()->getFirst(true);
	if (fabs(*slot) > EPSLON)
	{
		*slot = -*slot;
	}
	while (temp.getMatrix()->hasNext(true))
	{
		slot = temp.getMatrix()->next(true);
		if (fabs(*slot) > EPSLON)
		{
			*slot = -*slot;
		}
	}
	return temp;
}

MyMatrix MyMatrix::operator-(const MyMatrix& other) const
{
	MyMatrix temp = -other;
	return *this + temp;
}

MyMatrix MyMatrix::operator-=(const MyMatrix& other)
{
	*this = *this - other;
	return *this;
}

/**
* multiply this matrix with the other one and return the new matrix
*
* the method create an array of the new matrix to be then create a new matrix from it.
*
* due some implementetion difficulte i did it without the iterator
*/
MyMatrix MyMatrix::operator*(const MyMatrix& other) const
{
	unsigned int tmpRow, tmpCol;
	double* tmpArr;
	tmpRow = this->getRow();
	tmpCol = other.getCol();
	tmpArr = new double[tmpRow * tmpCol]();

	for (unsigned int row = 0; row < tmpRow; row++) 
	{
		for (unsigned int col = 0; col < tmpCol; col++) 
		{
			for (unsigned int i = 0; i < this->getCol(); i++)
			{
				tmpArr[tmpRow*col + row] += 
					this->getMatrix()->getElem(row, i)*other.getMatrix()->getElem(i, col);
			}
		}
	}
	MyMatrix temp(tmpArr, tmpRow, tmpCol);
	delete[] tmpArr;
	return temp;
}

MyMatrix MyMatrix::operator*=(const MyMatrix& other)
{
	*this = (*this) * other;
	return *this;
}

/**
* return true iff all values are equals
*
* using my iterator method
* in case of sparse matrix the iterator run only on non-zero values
*/
bool MyMatrix::operator==(const MyMatrix& other) const
{
	//check some fast way to decide equality
	if (this == &other)
	{
		return true;
	}
	if ((_zeroSum != other._zeroSum) || (getRow() != other.getRow()) || (getCol() != other.getCol()))
	{
		return false;
	}

	double* lhs = this->getMatrix()->getFirst(true);
	double* rhs = other.getMatrix()->getFirst(true);
	if (fabs(*lhs - *rhs) > EPSLON)
	{
		return false;
	}
	while (this->getMatrix()->hasNext(true) && this->getMatrix()->hasNext(true))
	{
		lhs = this->getMatrix()->next(true);
		rhs = other.getMatrix()->next(true);
		if (fabs(*lhs - *rhs) > EPSLON)
		{
			return false;
		}
	}
	return true;
}

double MyMatrix::trace() const
{
	double sum = 0;
	if (getRow() != getCol())
	{
		return sum;
	}
	for (unsigned int i = 0; i < getRow(); i++)
	{
		sum += (getMatrix()->getElem(i, i));
	}
	return sum;
}

/**
* return the frobenius norm of the matrix
*
* frobenius norm - sum of the matrix values square
*
* using my iterator method
* in case of sparse matrix the iterator run only on non-zero values
*/
double MyMatrix::frobeniusNorm() const
{
	if (_zeroSum == getRow() * getCol())
	{
		return 0;
	}
	double* data = getMatrix()->getFirst(true);
	double sum = (*data)*(*data);
	while (getMatrix()->hasNext(true))
	{
		data = getMatrix()->next(true);
		sum += (*data)*(*data);
	}
	return sum;
}

/**
* ostream for the givan matrix
*
* using my iterator method
*/
ostream& operator<<(ostream& os, const MyMatrix& matrix)
{
	if (matrix.isEmpty())
	{
		os << EMPTY_MAT;
		return os;
	}
	double* iter = matrix.getMatrix()->getFirst();
	for (unsigned int r = 0; r < matrix.getMatrix()->getRow(); r++)
	{
		os << setprecision(PRECISON + (int)log10(*iter)) << *iter;
		for (unsigned int c = 1; c < matrix.getMatrix()->getCol(); c++)
		{
			os << COMMA;
			iter = matrix.getMatrix()->next();
			os << setprecision(PRECISON + (int)log10(*iter)) << *iter;
		}
		iter = matrix.getMatrix()->next();
		os << NEW_LINE;
	}
	return os;
}

bool MyMatrix::isEmpty() const
{
	return (_zeroSum == getRow() * getCol());
}