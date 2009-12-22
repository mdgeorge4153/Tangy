/*
 * algebra.h - numbers of the form [a1 + a2*sqrt(2) + a3*sqrt(3) + a4*sqrt(4)]/d
 *
 */

#ifndef __tangy_algebra_h__
#define __tangy_algebra_h__ 1

#include <complex>
#include <valarray>

using std::valarray;
using std::basic_ostream;

/*
** ExtendedRational ************************************************************
*/

class ExtendedRational
{
public:
	////////////////////////////////////////////////////////////////////////////
	// public constructors                                                    //
	////////////////////////////////////////////////////////////////////////////

	ExtendedRational(int a1 = 0,
	                 int a2 = 0,
	                 int a3 = 0,
	                 int a4 = 0,
	                 unsigned int d  = 1);

	////////////////////////////////////////////////////////////////////////////
	// copying                                                                //
	////////////////////////////////////////////////////////////////////////////

	ExtendedRational(const ExtendedRational &);
	ExtendedRational & operator= (const ExtendedRational &);

	////////////////////////////////////////////////////////////////////////////
	// conversion operators                                                   //
	////////////////////////////////////////////////////////////////////////////

	operator float  () const;
	operator double () const;

	////////////////////////////////////////////////////////////////////////////
	// operator overloading                                                   //
	////////////////////////////////////////////////////////////////////////////

	ExtendedRational & operator+= (const ExtendedRational & other);
	ExtendedRational & operator*= (const ExtendedRational & other);
	ExtendedRational & operator-= (const ExtendedRational & other);
	ExtendedRational & operator/= (const ExtendedRational & other);

	ExtendedRational & operator+= (int other);
	ExtendedRational & operator*= (int other);
	ExtendedRational & operator-= (int other);
	ExtendedRational & operator/= (int other);

	friend bool             operator== (const ExtendedRational & a, const ExtendedRational & b);
	friend bool             operator<= (const ExtendedRational & a, const ExtendedRational & b);
	friend ExtendedRational operator/  (int, const ExtendedRational &);
                                                     
	template<typename Ch, typename Tr>
	friend basic_ostream<Ch, Tr>& operator<< (basic_ostream<Ch,Tr> &, const ExtendedRational &);

private:

	valarray<int> _n;
	int  _d;

	ExtendedRational inv()   const;
	ExtendedRational conj2() const;
	ExtendedRational conj3() const;

	void reduce ();
};

ExtendedRational operator+ (const ExtendedRational & a, const ExtendedRational & b);
ExtendedRational operator- (const ExtendedRational & a, const ExtendedRational & b);
ExtendedRational operator* (const ExtendedRational & a, const ExtendedRational & b);
ExtendedRational operator/ (const ExtendedRational & a, const ExtendedRational & b);

ExtendedRational operator+ (const ExtendedRational & a, int b);
ExtendedRational operator- (const ExtendedRational & a, int b);
ExtendedRational operator* (const ExtendedRational & a, int b);
ExtendedRational operator/ (const ExtendedRational & a, int b);

ExtendedRational operator+ (int a, const ExtendedRational & b);
ExtendedRational operator- (int a, const ExtendedRational & b);
ExtendedRational operator* (int a, const ExtendedRational & b);
ExtendedRational operator/ (int a, const ExtendedRational & b);

ExtendedRational operator+ (const ExtendedRational & a);
ExtendedRational operator- (const ExtendedRational & a);

bool operator== (const ExtendedRational & a, const ExtendedRational & b);
bool operator!= (const ExtendedRational & a, const ExtendedRational & b);

bool operator<= (const ExtendedRational & a, const ExtendedRational & b);
bool operator<  (const ExtendedRational & a, const ExtendedRational & b);
bool operator>= (const ExtendedRational & a, const ExtendedRational & b);
bool operator>  (const ExtendedRational & a, const ExtendedRational & b);

template<typename Ch, typename Tr>
basic_ostream<Ch, Tr>& operator<< (basic_ostream<Ch,Tr> &, const ExtendedRational &);


/*
** Vector type *****************************************************************
*/

typedef std::complex<ExtendedRational> Vector;

/*
** Constants *******************************************************************
*/

static const ExtendedRational SQRT1 = 1;
static const ExtendedRational SQRT2 (0,1,0,0,1);
static const ExtendedRational SQRT3 (0,0,1,0,1);
static const ExtendedRational SQRT6 (0,0,0,1,1);

static const ExtendedRational COS45 = SQRT2/2;
static const ExtendedRational SIN45 = SQRT2/2;
static const ExtendedRational COS30 = SQRT3/2;
static const ExtendedRational SIN30 = ExtendedRational(1)/2;


static const Vector ROT45 (COS45, SIN45);
static const Vector ROT30 (COS30, SIN30);
static const Vector ROT15 = ROT45 / ROT30;

#include "algebra.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
