/*
 * algebra.cc - implementation of algebra.h
 */

#include <algorithm>

Number::
Number (int a1, int a2, int a3, int a6, unsigned int d)
{
	_n[0] = a1;
	_n[1] = a2;
	_n[2] = a3;
	_n[3] = a6;

	_d    = d;

	reduce();
}

Number::
Number (const Number & other)
{
	_d = other._d;
	std::copy(other.begin(), other.end(), begin());
}

Number &
Number::
operator= (const Number & other)
{
	_d = other._d;
	std::copy(other.begin(), other.end(), begin());

	return (* this);
}

Number::
operator float () const
{
	// TODO
}

Number::
operator double () const
{
	// TODO
}

Number &
Number::
operator+= (const Number & other)
{
	for (int i = 0; i < 4; i++)
		_n[i] = _n[i] * other._d + other._n[i];

	_d *= other._d;

	reduce();

	return (* this);
}

Number &
operator-= (const Number & other)
{
	for (int i = 0; i < 4; i++)
		_n[i] = _n[i] * other._d - other._n[i];

	_d *= other._d;

	reduce();

	return (* this);
}

Number &
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

Number
Number::
inv () const
{
	Number result  = (*this);

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
	assert(!result._n[1] && !result._n[2] && !result._n[3]);

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
	return b == 0 ? a : gcd(a, a%b);
}

void
Number::
reduce ()
{
	int divisor = accumulate(begin(), end(), _d, *gcd);

	for (int i = 0; i < 3; i++)
		_n[i] /= divisor;

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
	return float(a) <= float(b);
}

/*
** vim: syntax=cpp ts=4 sw=4 cindent
*/
