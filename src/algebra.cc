/*
 * algebra.cc - implementation of algebra.h
 */

#include "algebra.h"
#include <cmath>
#include <cassert>
#include <numeric>
#include <stdexcept>
#include <iostream>

ExtendedRational::
ExtendedRational (int a1, int a2, int a3, int a6, unsigned int d)
	: _n(4)
{
	_n[0] = a1;
	_n[1] = a2;
	_n[2] = a3;
	_n[3] = a6;

	_d    = d;

	if (_d == 0)
	{
		throw std::logic_error("denominator must be non-zero");
	}

	reduce();
}

ExtendedRational::
ExtendedRational (const ExtendedRational & other)
	: _n (other._n), _d (other._d)
{
}

ExtendedRational &
ExtendedRational::
operator= (const ExtendedRational & other)
{
	_n = other._n;
	_d = other._d;

	return (* this);
}

ExtendedRational::
operator float () const
{
	return (_n[0] + _n[1]*sqrt(2.0f) + _n[2]*sqrt(3.0f) + _n[3]*sqrt(6.0f)) / _d;
}

ExtendedRational::
operator double () const
{
	return (_n[0] + _n[1]*sqrt(2.0)  + _n[2]*sqrt(3.0)  + _n[3]*sqrt(6.0)) / _d;
}

ExtendedRational &
ExtendedRational::
operator+= (const ExtendedRational & other)
{
	_n = _n * other._d + _d * other._n;

	_d *= other._d;

	reduce();

	return (* this);
}

ExtendedRational &
ExtendedRational::
operator-= (const ExtendedRational & other)
{
	_n = _n * other._d - _d * other._n;

	_d *= other._d;

	reduce();

	return (* this);
}

ExtendedRational &
ExtendedRational::
operator*= (const ExtendedRational & other)
{
	long a1 = _n[0];
	long a2 = _n[1];
	long a3 = _n[2];
	long a6 = _n[3];

	long b1 = other._n[0];
	long b2 = other._n[1];
	long b3 = other._n[2];
	long b6 = other._n[3];


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

ExtendedRational &
ExtendedRational::
operator+= (int other)
{
	_n[0] += other * _d;
	reduce ();

	return (* this);
}

ExtendedRational &
ExtendedRational::
operator-= (int other)
{
	_n[0] -= other * _d;
	reduce ();

	return (* this);
}

ExtendedRational &
ExtendedRational::
operator*= (int other)
{
	_n *= other;
	reduce ();

	return (* this);
}

ExtendedRational &
ExtendedRational::
operator/= (int other)
{
	_d *= other;
	reduce ();

	return (* this);
}

ExtendedRational
ExtendedRational::
inv () const
{
	ExtendedRational result  = (*this);

	if (_n[0] == 0 && _n[1] == 0 && _n[2] == 0 && _n[3] == 0)
		throw std::logic_error("divide by zero");

	//
	// result = (*this) * factor1
	//
	ExtendedRational factor1 = conj2();
	result *= factor1;
	assert(!result._n[1] && !result._n[3]);

	//
	// result = (*this) * factor1 * factor2
	//
	ExtendedRational factor2 = conj3();
	result *= factor2;
	assert(result._n[0] && !result._n[1] && !result._n[2] && !result._n[3]);

	//                       1
	// result = ---------------------------
	//          (*this) * factor1 * factor2
	long d       = result._d;
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

ExtendedRational
ExtendedRational::
conj2 () const
{
	ExtendedRational result = (* this);
	result._n[1] = - result._n[1];
	result._n[3] = - result._n[3];
	return result;
}

ExtendedRational
ExtendedRational::
conj3 () const
{
	ExtendedRational result = (* this);
	result._n[2] = - result._n[2];
	result._n[3] = - result._n[3];
	return result;
}

static
long
gcd(long a, long b)
{
	return b == 0 ? a : gcd(b, a%b);
}

void
ExtendedRational::
reduce ()
{
	long divisor = std::accumulate(&(_n[0]), &(_n[4]), _d, *gcd);

	if (divisor * _d < 0)
		divisor = -divisor;
	_n /= divisor;
	_d /= divisor;
}

bool
operator== (const ExtendedRational & a, const ExtendedRational & b)
{
	for (int i = 0; i < 3; i++)
		if (a._n[i] != b._n[i])
			return false;

	if (a._d != b._d)
		return false;

	return true;
}

bool
operator<= (const ExtendedRational & a, const ExtendedRational & b)
{
	if (a == b)
		return true;

	// TODO -- imprecise
	return double(a) <= double(b);
}

std::complex<float>
approximate (std::complex<ExtendedRational> n)
{
	return std::complex<float> (n.real(), n.imag());
}

static const float PI = 3.14159265;

Vector
normalize (const Vector & v)
{
	//
	// perhaps there is a better algorithm?
	//

	float theta = atan2(v.real(), v.imag());

	std::cout << v << ": " << theta;

	if (theta < 0)
		theta += 2 * PI;

	theta /= PI;  // theta in [0, 2)
	theta *= 12;  // theta in [0, 24)
	theta += 0.5; // turn floor into round

	int n = int(theta) % 24;
	
	std::cout << " --> " << n << std::endl;

	return std::pow(ROT15, n);
}

/*
** vim: syntax=cpp ts=4 sw=4 cindent
*/
