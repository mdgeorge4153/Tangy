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
	typedef std::valarray<point>         point_container;

	friend class TanSet<GameTraits>;

	/////////////////////
	// public mutators //
	/////////////////////

	void flip();
	void set_pos (const point  &);
	void set_rot (const vector &);

	void pacify();

	//////////////////////
	// public accessors //
	//////////////////////

	bool is_offset   () const;

	const vector_container & shape   () const;
	const point            & pos     () const;
	const point            & desired () const;

	bool contains (const point &) const;

private:

	/////////////////////
	// private members //
	/////////////////////

	bool             _selected;
	point            _pos;
	point            _desired_pos;
	vector_container _shape;

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

	typedef typename GameTraits::tan   tan;
	typedef typename GameTraits::point point;

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

	//////////////////////
	// public accessors //
	//////////////////////

	const container& tans      () const;
	const tan&       selection () const;

	tan * find(const point &) const;

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
