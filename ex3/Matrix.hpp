/**
* Matrix.hpp
*
* -------------------------------------------------------------------------------------------------
* General:		This class represents a generic matrix and can operate thing such as M+N, M*N
*				and more.
*				The matrix can be of any number type that support +, *, = , <<.
*
* MyMatrix			- default constructor
*					  create the zero element of the number
*
*					- class constructor
*					  create a new colSizeXrowSize matrix from the values in the vector
*
*					- copy constructor
*
*					- move constructor
*
* ~MyMatrix			- class destructor
*
* operator=			- assign the other matrix into this
*
* operator<<		- ostream for the givan matrix
*
* operator+			- add this matrix with the other one and return the new matrix
*
* operator*			- matrix*matrix - multiply this matrix with the other one and return the new matrix
*					- matrix*scalar - multiply this matrix with the scalar and return the new matrix
*					- scalar*matrix - multiply this matrix with the scalar and return the new matrix
*
* transpose			- return a new matrix in size of colXrow from this rowXcol matrix
*					  such that new[i][j] = this[j][i]
*
* trace				- return true iff the matrix is square and assign the trace to the givan reference.
*					  return false if the matrix is not a square and assign 0 to the givan reference.
*					  trace - the sum of the diagonal values
*/
#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include <vector>
#include <iostream>
#include "Rational.h"
#include "MatrixExceptions.h"

/**
* General:		This class represents a generic matrix and can operate thing such as M+N, M*N
*				and more.
*				The matrix can be of any number type that support +, *, = , <<.
*/
template <class T>
class Matrix
{
public:
	/**
	* default constructor
	* create 1X1 matrix with the default of the number
	*/
	Matrix<T>()
	{
		_rows = 1;
		_cols = 1;
		T cell = T();
		std::vector<T> row;
		row.push_back(cell);
		_matrix.push_back(row);
	}

	/**
	* class constructor
	* create a new colSizeXrowSize matrix from the values in the vector
	*/
	Matrix<T>(const int& rows, const int& cols, const std::vector<T> cells) : _rows(rows), _cols(cols)
	{
		if ((int)cells.size() < rows * cols)
		{
			throw TooSmallVectorExcaption();
		}
		else if ((int)cells.size() > rows * cols)
		{
			throw TooBigVectorExcaption();
		}
		T cell;
		for (int r = 0; r < _rows; r++)
		{
			std::vector<T> row;
			for (int c = 0; c < _cols; c++)
			{
				cell = cells[r*_cols + c];
				row.push_back(cell);
			}
			_matrix.push_back(row);
		}
	}

	/**
	* copy constructor
	*/
	Matrix(const Matrix<T>& other) : _rows(other._rows), _cols(other._cols), _matrix(other._matrix)
	{

	}

	/**
	* move constructor
	*
	*/
	Matrix(Matrix<T> && other) :_rows(other._rows), _cols(other._cols),
								_matrix(move(other._matrix))
	{

	}

	/**
	* class destructor
	*
	*/
	~Matrix()
	{
		_cols = 0;
		_rows = 0;
		_matrix.clear();
	}

	/**
	* assign the other matrix into this using copy-and-swap.
	*
	*/
	Matrix& operator=(Matrix<T> other)
	{
		std::swap(_rows, other._rows);
		std::swap(_cols, other._cols);
		std::swap(_matrix, other._matrix);
		return *this;
	}

	/**
	* add this matrix with the other one and return the new matrix
	*
	*/
	Matrix operator+(const Matrix<T>& other) const
	{
		if (_cols != other._cols || _rows != other._rows)
		{
			throw WrongSizePlusExcaption();
		}
		else
		{
			std::vector<T> temp;
			for (int r = 0; r < _rows; r++)
			{
				for (int c = 0; c < _cols; c++)
				{
					temp.push_back(_matrix[r][c] + other._matrix[r][c]);
				}
			}
			return Matrix<T>(_rows, _cols, temp);
		}
	}

	/**
	* multiply this matrix with the other one and return the new matrix
	*
	*/
	Matrix operator*(const Matrix<T>& other) const
	{
		if (_cols != other._rows)
		{
			throw WrongSizeMulExcaption();
		}
		else
		{
			std::vector<T> temp;
			T cell;
			for (int r = 0; r < _rows; r++)
			{
				for (int c = 0; c < other._cols; c++)
				{
					cell = 0;
					for (int i = 0; i < _cols; i++)
					{
						cell = cell + _matrix[r][i] * other._matrix[i][c];
					}
					temp.push_back(cell);
				}
			}
			return Matrix<T>(_rows, other._cols, temp);
		}
	}

	/**
	* matrix*scalar - multiply this matrix with the scalar and return the new matrix
	*
	*/
	Matrix operator*(const T& scalar) const
	{

		std::vector<T> temp;
		T cell;
		for (int r = 0; r < _rows; r++)
		{
			for (int c = 0; c < _cols; c++)
			{
				cell = _matrix[r][c] * scalar;
				temp.push_back(cell);
			}
		}
		return Matrix<T>(_rows, _cols, temp);
	}

	/**
	* scalar*matrix - multiply this matrix with the scalar and return the new matrix
	*
	*/
	friend Matrix operator*(const T& scalar, const Matrix<T>& other)
	{
		return Matrix<T>(other * scalar);
	}

	/**
	* return a new matrix in size of colXrow from this rowXcol matrix
	* such that new[i][j] = this[j][i]
	*/
	Matrix transpose() const
	{
		std::vector<T> temp;
		for (int c = 0; c < _cols; c++)
		{
			for (int r = 0; r < _rows; r++)
			{
				temp.push_back(_matrix[r][c]);
			}
		}
		return Matrix<T>(_cols, _rows, temp);
	}

	/**
	* return true iff the matrix is square and assign the trace to the givan reference.
	* return false if the matrix is not a square and assign 0 to the givan reference.
	* trace - the sum of the diagonal values
	*
	*/
	bool hasTrace(T& trace) const
	{
		trace = 0;
		if (_rows != _cols)
		{
			return false;
		}
		else
		{
			for (int c = 0; c < _cols; c++)
			{
				trace = trace + _matrix[c][c];
			}
			return true;
		}
	}

	/**
	* ostream for the givan matrix
	*
	*/
	friend std::ostream& operator<<(std::ostream &os, const Matrix<T> &matrix)
	{
		for (int r = 0; r < matrix._rows; r++)
		{
			os << matrix._matrix[r][0];
			for (int c = 1; c < matrix._cols; c++)
			{
				os << " " << matrix._matrix[r][c];
			}
			os << "\n";
		}
		return os;
	}

private:
	int _rows;
	int _cols;
	std::vector<std::vector<T>> _matrix;

}; 


/**
* specialization for hasTrace generic method
* calculate the trace in case of Rational number in order to save time in fixing the rational
* number only once(at the end)
*/
template<>
bool Matrix<Rational>::hasTrace(Rational& trace) const
{
	std::cout << "Performing specialized function of trace for Rational values" << std::endl;
	trace = Rational(0);
	if (_rows != _cols)
	{
		return false;
	}
	else
	{
		long int numerator = _matrix[0][0].getNumerator();
		long int denominator = _matrix[0][0].getDenominator();
		for (int c = 1; c < _cols; c++)
		{
			numerator = numerator * _matrix[c][c].getDenominator() +
				_matrix[c][c].getNumerator() * denominator;
			denominator = denominator * _matrix[c][c].getDenominator();
		}
		trace = Rational(numerator, denominator);
		return true;
	}
}
#endif //_MATRIX_HPP_

