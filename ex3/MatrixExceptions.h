/**
* MatrixException.h
*
* excaption that may happend in Matrix class
* - exception in case of different in matrixs size in operator+
* - exception in case of different in matrixs size in operator*
* - exception in case of too much element in vector
* - exception in case of too less element in vector
*/
#include <iostream>
#include <exception>

#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

/**
* exception in case of different in matrixs size in operator+
*/
class WrongSizePlusExcaption : public std::exception
{
public:
	/**
	* message to display
	*/
	virtual const char* what() const throw()
	{
		return "matrixs are in different size";
	}
};
/**
* exception in case of different in matrixs size in operator*
*/
class WrongSizeMulExcaption : public std::exception
{
public:
	/**
	* message to display
	*/
	virtual const char* what() const throw()
	{
		return "Left column and right rows are in different size";
	}
};
/**
* exception in case of too much element in vector
*/
class TooBigVectorExcaption : public std::exception
{
public:
	/**
	* message to display
	*/
	virtual const char* what() const throw()
	{
		return "vector have an extra values";
	}
};
/**
* exception in case of too less element in vector
*/
class TooSmallVectorExcaption : public std::exception
{
public:
	/**
	* message to display
	*/
	virtual const char* what() const throw()
	{
		return "vector missing values";
	}
};
#endif //MATRIX_EXCEPTIONS_H
