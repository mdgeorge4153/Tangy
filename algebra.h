/*
 * algebra.h - numbers of the form [a1 + a2*sqrt(2) + a3*sqrt(3) + a4*sqrt(4)]/d
 *
 */

#ifndef __gtans_algebra_h__
#define __gtans_algebra_h__ 1

#include <iostream>
#include <complex>
#include <valarray>

using std::valarray;
using std::basic_ostream;

/*
** Numbers *********************************************************************
*/

class Number
{
public:
	////////////////////////////////////////////////////////////////////////////
	// public constructors                                                    //
	////////////////////////////////////////////////////////////////////////////

	Number(int a1 = 0,
	       int a2 = 0,
	       int a3 = 0,
	       int a4 = 0,
	       unsigned int d  = 1);

	////////////////////////////////////////////////////////////////////////////
	// copying                                                                //
	////////////////////////////////////////////////////////////////////////////

	Number(const Number &);
	Number & operator= (const Number &);

	////////////////////////////////////////////////////////////////////////////
	// conversion operators                                                   //
	////////////////////////////////////////////////////////////////////////////

	float  make_float  () const;
	double make_double () const;

	////////////////////////////////////////////////////////////////////////////
	// operator overloading                                                   //
	////////////////////////////////////////////////////////////////////////////

	Number & operator+= (const Number & other);
	Number & operator*= (const Number & other);
	Number & operator-= (const Number & other);
	Number & operator/= (const Number & other);

	friend bool operator== (const Number & a, const Number & b);
	friend bool operator<= (const Number & a, const Number & b);

	template<typename Ch, typename Tr>
	friend basic_ostream<Ch, Tr>& operator<< (basic_ostream<Ch,Tr> &, const Number &);

private:

	valarray<int> _n;
	int  _d;

	Number inv()   const;
	Number conj2() const;
	Number conj3() const;

	void reduce ();
};

Number operator+ (const Number & a, const Number & b);
Number operator- (const Number & a, const Number & b);
Number operator* (const Number & a, const Number & b);
Number operator/ (const Number & a, const Number & b);

Number operator+ (const Number & a);
Number operator- (const Number & a);

bool operator== (const Number & a, const Number & b);
bool operator!= (const Number & a, const Number & b);

bool operator<= (const Number & a, const Number & b);
bool operator<  (const Number & a, const Number & b);
bool operator>= (const Number & a, const Number & b);
bool operator>  (const Number & a, const Number & b);

template<typename Ch, typename Tr>
basic_ostream<Ch, Tr>& operator<< (basic_ostream<Ch,Tr> &, const Number &);


/*
** Complex Numbers *************************************************************
*/

typedef std::complex<Number> Vector;


/*
** Constants *******************************************************************
*/

static const Number SQRT1 = 1;
static const Number SQRT2 (0,1,0,0,1);
static const Number SQRT3 (0,0,1,0,1);
static const Number SQRT6 (0,0,0,1,1);

static const Number COS45 = SQRT2/2;
static const Number SIN45 = SQRT2/2;
static const Number COS30 = SQRT3/2;
static const Number SIN30 = Number(1)/2;

static const Vector ROT45 (COS45, SIN45);
static const Vector ROT30 (COS30, SIN30);
static const Vector ROT15 = ROT45 / ROT30;

#include "algebra.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
