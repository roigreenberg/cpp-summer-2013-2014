/**
* RationalException.h
*
* excaption that may happend in Rational class
* - exception in case of division by zero
*/
#include <iostream>
#include <exception>

#ifndef RATIONAL_EXCEPTIONS_H
#define RATIONAL_EXCEPTIONS_H

/**
* exception in case of division by zero
*/
class DivisionByZeroExceptions : public std::exception
{
public:
	/**
	* message to display
	*/
	virtual const char* what() const throw()
	{
		return "division by zero";
	}
};

#endif // RATIONAL_EXCEPTIONS_H