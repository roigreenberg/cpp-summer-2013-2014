/**
* Rational - class to represent a ratioanl number - a ratio between two
* integers.
*/
#include <string>
#include <sstream>
#include "Rational.h"
#include "RationalExceptions.h"

#define DEFAULT_NUMINATOR 0
#define DEFAULT_DENOMINATOR 1
#define FRACTION '/'

/**
* Constructors geting int or default which is set to 0
*/
Rational::Rational(const long int &value)
{
	_numerator = value;
	_denominator = 1;
}
/**
* Constructors geting numerator and denominator
*/
Rational::Rational(const long int &numerator, const long int &denominator)
{
	_numerator = numerator;
	{
		if (denominator == 0)
		{
			throw DivisionByZeroExceptions();
		}
		_denominator = denominator;
	}
	_fixZero();
	_makeRepresentationCoprime();
	_fixNegativity();
}
/**
* Constructors by string "numerator/denominator"
*/
Rational::Rational(const std::string &str)
{
	char split_char = FRACTION;
	std::string temp;
	std::string tempDenomerator;
	std::istringstream number(str);
	
	std::getline(number, temp, split_char);
	_numerator = std::stoi(temp);

	std::getline(number, temp, split_char);
	_denominator = std::stoi(temp);

	if (_denominator == 0)
	{
		throw DivisionByZeroExceptions();
	}

	_fixZero();
	_makeRepresentationCoprime();
	_fixNegativity();
}

/**
* Constructors copy constructor
*/
Rational::Rational(const Rational &other)
{
	_numerator = other._numerator;
	_denominator = other._denominator;
}
/**
* Constructors move constructor
*/
Rational::Rational(Rational && other)
{
	_numerator = other._numerator;
	_denominator = other._denominator;
}

/**
* Assignment operator, use copy-and-swap idiom
*/
Rational& Rational::operator=(Rational other)
{
	std::swap(_numerator, other._numerator);
	std::swap(_denominator, other._denominator);
	return *this;
}

/**
* Returns the numerator
*/
const long int Rational::getNumerator() const
{
	return _numerator;
}
/**
* Returns the denominator
*/
const long int Rational::getDenominator() const
{
	return _denominator;
}

/**
* Summing two Rationals
* Addition should be calculated in the way we calculate addition of 2
* ratios (using their common denominator).
*/
const Rational Rational::operator+(const Rational &other) const
{

	Rational result(_numerator * other._denominator + other._numerator * _denominator, 
		_denominator * other._denominator);

	result._fixZero();
	result._makeRepresentationCoprime();
	result._fixNegativity();

	return result;

}
/**
* Multiplying operator for Rational
* Multiplication should be calculated in the way we calculate
* multiplication of 2 ratios (separately for the numerator and for the
* denominator).
*/
const Rational Rational::operator*(const Rational &other) const
{
	Rational result(_numerator * other._numerator, other._denominator * _denominator);

	result._fixZero();
	result._makeRepresentationCoprime();
	result._fixNegativity();

	return result;
}

/**
* operator<< for stream insertion
* The format is numerator/denominator w/o spaces or addional characters
*/
std::ostream& operator<<(std::ostream &os, const Rational &number)
{
	os << number._numerator << FRACTION << number._denominator;
	return os;
}

void Rational::_fixZero()
{
	if (_numerator == 0)
	{
		_numerator = DEFAULT_NUMINATOR;
		_denominator = DEFAULT_DENOMINATOR;
	}
}
void Rational::_fixNegativity()
{
	if (_denominator < 0)
	{
		_denominator = -_denominator;
		_numerator = -_numerator;
	}
}
void Rational::_makeRepresentationCoprime()
{
	if (_numerator != 1 && _denominator != 1)
	{
		long int gcd = _greatestCommonDivisor(_numerator, _denominator);
		_numerator /= gcd;
		_denominator /= gcd;
	}
}

const long int Rational::_greatestCommonDivisor(const long int &a, const long int &b)
{
	if (b == 0)
	{
		return a;
	}
	else
	{
		return _greatestCommonDivisor(b, a % b);
	}
}
