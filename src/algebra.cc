/*
 * algebra.cc - implementation of algebra.h
 */

#include "algebra.h"
#include <cmath>
#include <cassert>
#include <numeric>
#include <stdexcept>

Number::
Number (int a1, int a2, int a3, int a6, unsigned int d)
	: _n(4)
{
	_n[0] = a1;
	_n[1] = a2;
	_n[2] = a3;
	_n[3] = a6;

	_d    = d;

	if (_d == 0)
	{
		std::cerr << "div by zero" << std::endl;
		throw std::logic_error("denominator must be non-zero");
	}

	reduce();
}

Number::
Number (const Number & other)
	: _n (other._n), _d (other._d)
{
}

Number &
Number::
operator= (const Number & other)
{
	_n = other._n;
	_d = other._d;

	return (* this);
}

Number::
operator float () const
{
	return _n[0] + _n[1]*sqrt(2.0f) + _n[2]*sqrt(3.0f) + _n[6]*sqrt(6.0f);
}

Number::
operator double () const
{
	return _n[0] + _n[1]*sqrt(2.0)  + _n[2]*sqrt(3.0)  + _n[3]*sqrt(6.0);
}

Number &
Number::
operator+= (const Number & other)
{
	_n = _n * other._d + _d * other._n;

	_d *= other._d;

	reduce();

	return (* this);
}

Number &
Number::
operator-= (const Number & other)
{
	_n = _n * other._d - _d * other._n;

	_d *= other._d;

	reduce();

	return (* this);
}

Number &
Number::
operator*= (const Number & other)
{
	int a1 = _n[0];
	int a2 = _n[1];
	int a3 = _n[2];
	int a6 = _n[3];

	int b1 = other._n[0];
	int b2 = other._n[1];
	int b3 = other._n[2];
	int b6 = other._n[3];


	//     *    ||    1      |  sqrt(2)  |  sqrt(3)  |  srqt(6) 
	// =========++===========+===========+===========+===========
	//     1    ||    1      |  sqrt(2)  |  sqrt(3)  |  sqrt(6) 
	// ---------++-----------+-----------+-----------+-----------
	//  sqrt(2) ||  sqrt(2)  |     2     |  sqrt(6)  | 2*sqrt(3)
	// ---------++-----------+-----------+-----------+-----------
	//  sqrt(3) ||  sqrt(3)  |  sqrt(6)  |     3     | 3*sqrt(2)
	// ---------++-----------+-----------+-----------+-----------
	//  sqrt(6) ||  sqrt(6)  | 2*sqrt(3) | 3*sqrt(2) |     6


	_n[0] =   a1*b1 + 2*a2*b2 + 3*a3*b3 + 6*a6*b6;
	_n[1] =   a1*b2 +   a2*b1 + 3*a3*b6 + 3*a6*b3;
	_n[2] =   a1*b3 + 2*a2*b6 +   a3*b1 + 2*a6*b2;
	_n[3] =   a1*b6 +   a2*b3 +   a3*b2 +   a6*b1;

	_d *= other._d;

	reduce();

	return (*this);
}

Number &
Number::
operator+= (int other)
{
	_n[0] += other * _d;
	reduce ();
}

Number &
Number::
operator-= (int other)
{
	_n[0] -= other * _d;
	reduce ();
}

Number &
Number::
operator*= (int other)
{
	_n *= other;
	reduce ();
}

Number &
Number::
operator/= (int other)
{
	_d *= other;
	reduce ();
}

Number
Number::
inv () const
{
	Number result  = (*this);

	if (_n[0] == 0 && _n[1] == 0 && _n[2] == 0 && _n[3] == 0)
		throw std::logic_error("divide by zero");

	//
	// result = (*this) * factor1
	//
	Number factor1 = conj2();
	result *= factor1;
	assert(!result._n[1] && !result._n[3]);

	//
	// result = (*this) * factor1 * factor2
	//
	Number factor2 = conj3();
	result *= factor2;
	assert(result._n[0] && !result._n[1] && !result._n[2] && !result._n[3]);

	//                       1
	// result = ---------------------------
	//          (*this) * factor1 * factor2
	int d        = result._d;
	result._d    = result._n[0];
	result._n[0] = d;

	//                  1
	// result = -----------------
	//          (*this) * factor2
	result *= factor1;

	//             1
	// result = -------
	//          (*this)
	result *= factor2;

	return result;
}

Number
Number::
conj2 () const
{
	Number result = (* this);
	result._n[1] = - result._n[1];
	result._n[3] = - result._n[3];
	return result;
}

Number
Number::
conj3 () const
{
	Number result = (* this);
	result._n[2] = - result._n[2];
	result._n[3] = - result._n[3];
	return result;
}

static
int 
gcd(int a, int b)
{
	return b == 0 ? a : gcd(b, a%b);
}

void
Number::
reduce ()
{
	int divisor = std::accumulate(&(_n[0]), &(_n[4]), _d, *gcd);

	if (divisor * _d < 0)
		divisor = -divisor;
	_n /= divisor;
	_d /= divisor;
}

bool
operator== (const Number & a, const Number & b)
{
	for (int i = 0; i < 3; i++)
		if (a._n[i] != b._n[i])
			return false;

	if (a._d != b._d)
		return false;

	return true;
}

bool
operator<= (const Number & a, const Number & b)
{
	if (a == b)
		return true;

	// TODO -- imprecise
	return double(a) <= double(b);
}

/*
** vim: syntax=cpp ts=4 sw=4 cindent
*/
