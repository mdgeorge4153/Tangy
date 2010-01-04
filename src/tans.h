/*
 * tans.h - interface for manipulating sets of tans.
 */

#ifndef __tangy_tans_h__
#define __tangy_tans_h__ 1

#include <vector>
#include <valarray>
#include <complex>

/*
********************************************************************************
*/

template<typename> class Tan;
template<typename> class TanSet;

/*
********************************************************************************
*/

template<typename GameTraits>
class Tan
{
public:

	//////////////////
	// public types //
	//////////////////

	typedef typename GameTraits::point   point;
	typedef typename GameTraits::vector  vector;
	typedef std::valarray<vector>        vector_container;

	friend class TanSet<GameTraits>;

	/////////////////////
	// public mutators //
	/////////////////////

	void flip     ();
	void set_pos  (const point  &);
	void set_rot  (const vector &);

	//////////////////////
	// public accessors //
	//////////////////////

	const vector_container & shape () const;

	const point  & pos  () const;
	const vector & rot  () const;
	const bool     conj () const;

	template<typename OutputIterator>
	OutputIterator points (OutputIterator) const;

	bool contains (const point &) const;

protected:

	/////////////////////
	// private members //
	/////////////////////

	point            _pos;
	vector           _rot;
	bool             _conj;

	vector_container _shape;

	mutable std::vector<point> _points;
	mutable bool               _points_valid;

	Tan ();
	Tan (const point &, const point &, const point &);
	Tan (const point &, const point &, const point &, const point &);

};

/*
********************************************************************************
*/

template<typename GameTraits>
class TanSet
{
public:

	//////////////////
	// public types //
	//////////////////

	typedef typename GameTraits::tan    tan;
	typedef typename GameTraits::point  point;
	typedef typename GameTraits::vector vector;

	typedef typename GameTraits::tan_container    container;
	typedef typename GameTraits::tan_handle       tan_handle;
	typedef typename GameTraits::const_tan_handle const_tan_handle;

	/////////////////////////
	// public constructors //
	/////////////////////////

	TanSet ();

	/////////////////////
	// public mutators //
	/////////////////////

	void pan (const vector &);

	//////////////////////
	// public accessors //
	//////////////////////

	const_tan_handle find (const point &) const;
	      tan_handle find (const point &);

	const_tan_handle begin () const;
	      tan_handle begin ();

	const_tan_handle end () const;
	      tan_handle end ();

protected:

	/////////////////////
	// private members //
	/////////////////////

	container _tans;
};

/*
********************************************************************************
*/

#include "tans.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
