/*
 * tans.h - interface for manipulating sets of tans.
 */

#ifndef __gtans_tans_h__
#define __gtans_tans_h__ 1

#include <vector>
#include <valarray>
#include <complex>

/*
********************************************************************************
*/

template<typename>                  class Tan;
template<typename,
         template <typename> class> class TanSet;
template<typename>                  class FreePlacement;

/*
********************************************************************************
*/

template<typename Number>
class Tan
{
public:
	typedef typename std::complex<Number>  point;
	typedef typename std::complex<Number>  vector;
	typedef typename std::valarray<vector> vector_container;
	typedef typename std::valarray<point>  point_container;

	bool is_selected () const;
	bool is_offset   () const;

	const vector_container & shape   () const;
	const point            & pos     () const;
	const point            & desired () const;

	template<typename, template<typename> class>
	friend class TanSet;

private:
	bool             _selected;
	point            _pos;
	point            _desired_pos;
	vector_container _shape;

	Tan ();
	Tan (point, point, point);
	Tan (point, point, point, point);

	template<typename N>
	Tan (const Tan<N> &);
};

/*
********************************************************************************
*/

template<typename Number = float,
         template <typename> class PlacementPolicy = FreePlacement
		 >
class TanSet
	: public PlacementPolicy<Number>
{
public:
	typedef Tan<Number>      tan;
	typedef std::vector<tan> container;

	TanSet ();

	template<typename TS>
	TanSet (const TS &);

	void begin_motion (int, int);
	void move         (int, int);
	void flip         ();
	void rotate       (float);
	void end_motion   ();

	void set_size     (int, int);

	template<typename PointIter>
	void add_obstacle (PointIter, PointIter);

	const container& tans      () const;
	const tan&       selection () const;

	virtual void operator~ ();

protected:

	container _tans;
	int       _selection;
};

/*
********************************************************************************
*/

template<typename N>
class FreePlacement
{

};

/*
********************************************************************************
*/

#include "tans.hcc"

#endif

/*
** vim: ts=4 sw=4 cindent
*/
