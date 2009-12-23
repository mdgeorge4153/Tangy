/*
 * tans.h - interface for manipulating sets of tans.
 */

#ifndef __tangy_tans_h__
#define __tangy_tans_h__ 1

#include <vector>
#include <valarray>
#include <complex>

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

	void pacify();

	//////////////////////
	// public accessors //
	//////////////////////

	const vector_container & shape () const;

	const point  & pos  () const;
	const vector & rot  () const;
	const bool     conj () const;

	template<typename OutputIterator>
	OutputIterator points (OutputIterator) const;

	bool is_offset   () const;

	const point  & desired_pos () const;
	const vector & desired_rot () const;

	bool contains (const point &) const;

protected:

	/////////////////////
	// private members //
	/////////////////////

	point            _pos;
	point            _desired_pos;

	vector           _rot;
	vector           _desired_rot;

	bool             _conj;

	vector_container _shape;

	mutable std::vector<point> _points;
	mutable bool               _points_valid;

	Tan ();
	Tan (point, point, point);
	Tan (point, point, point, point);

	template<typename GT>
	Tan (const Tan<GT> &);
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

	typedef std::vector<tan>         container;

	/////////////////////////
	// public constructors //
	/////////////////////////

	TanSet ();

	template<typename TS>
	TanSet (const TS &);

	/////////////////////
	// public mutators //
	/////////////////////

	void set_size     (int, int);

	template<typename PointIter>
	void add_obstacle (PointIter, PointIter);

	void pan (const vector &);

	//////////////////////
	// public accessors //
	//////////////////////

	const container& tans      () const;
	const tan&       selection () const;

	const tan * find (const point &) const;
	      tan * find (const point &);

protected:

	/////////////////////
	// private members //
	/////////////////////

	container _tans;
	int       _selection;
};

/*
********************************************************************************
*/

#include "tans.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
